#!/bin/bash
# Orchestrate one matching round (see PLAN.md sections 4 and 6). Run from the main checkout.
#
#   round.sh start [--force] <assignments-file>
#   round.sh status
#   round.sh integrate <agent-k> [hash...]
#   round.sh finish [--remove-worktrees] [--park <prefix>] [--force]
#   round.sh farm-list [--plain]
#
# Env: ROUND_BASE (default match-round-1) = the branch agents start from and picks land on.
#      ROUND_MAIN (default: the main checkout) = the checkout that integrates/builds; agent
#      worktrees go under $ROUND_MAIN/.claude/worktrees.
#      ROUND_DIGEST=0 (start: no DIGEST_<func>.md), ROUND_DIGEST_FULL=1 (digest.py without --fast,
#      i.e. with the ido_bisect default set), ROUND_DIGEST_JOBS (default 4 parallel digests).
set -u

usage() {
    cat <<'EOF'
usage: matching_notes/round.sh <command> [options]
env:   ROUND_BASE=<branch>  (default match-round-1)   ROUND_MAIN=<checkout> (default: main checkout)
       ROUND_DIGEST=0 | ROUND_DIGEST_FULL=1 | ROUND_DIGEST_JOBS=<n>   (start: oracle digests, below)

  start [--force] <assignments-file>
      One line per agent:  agent-k: func_A[@score]:src/a.c func_B[@score]:src/b.c ...
      ('#' starts a comment). For each agent: git worktree add --detach
      .claude/worktrees/agent-k $ROUND_BASE, run agent_setup.sh, mkdir scratch_agent/, write
      PROMPT.md (matching_notes/round_prompt_template.md + matcher rules from PLAN.md + each
      function's NOTES.md entries and score). Refuses if any worktree already exists (--force
      removes it first, discarding its work) or the main checkout has uncommitted tracked changes.
      Then, per function, digest.py FUNC --src SRC --repo <worktree> --out <worktree>/DIGEST_FUNC.md
      (one-page summary of the five oracles; PROMPT.md tells the agent to read it before step
      zero), $ROUND_DIGEST_JOBS (default 4) at a time in the background, --fast unless
      ROUND_DIGEST_FULL=1; ROUND_DIGEST=0 skips digests. A failed digest only prints a WARNING
      (log: <worktree>/scratch_agent/digest_FUNC.log).

  status
      Per worktree: HEAD, commits in $ROUND_BASE..HEAD, modified tracked files, and whether the
      committed diff adds an '#if 1' line under src/.

  integrate <agent-k> [hash...]
      Cherry-pick onto $ROUND_BASE (must be checked out in the main checkout) the given commits, or
      by default ALL of $ROUND_BASE..HEAD of that worktree, oldest first (commits whose patch is
      already in $ROUND_BASE are skipped). Stops before a commit that adds '#if 1' under src/ or
      include/, and aborts+stops on a conflict. Then full build (must print OK), GLOBAL_ASM count,
      progress, and the list of newly matched functions. Never resets anything.

  finish [--remove-worktrees] [--park <prefix>] [--force]
      --remove-worktrees: for each agent worktree with commits in $ROUND_BASE..HEAD, create branch
        <prefix>-agent-k (default prefix 'parked') at its HEAD, then git worktree remove --force +
        prune. A worktree with modified tracked files is skipped unless --force.
      Then delete stale asm/us/nonmatchings/**/*.s (not named by any GLOBAL_ASM in src/) - only
      when no agent worktree is left (asm/ is shared by symlink), or with --force - rebuild,
      print progress, and refresh the corpus index (corpus.py build).

  farm-list [--plain]
      Open functions as 'func:src/file.c' lines for palmetto_job.sh FUNCS (tier annotations as
      '# comments'; --plain drops them, for FUNCS_OVERRIDE).
EOF
}

# ---------------------------------------------------------------- setup
SCRIPT_DIR=$(cd "$(dirname "$0")" && pwd)
# MAIN = the checkout the round integrates into: the main checkout (even if this script is run
# from inside an agent worktree), or ROUND_MAIN (a staged copy / test worktree of the same repo).
MAIN=${ROUND_MAIN:-$(dirname "$(git -C "$SCRIPT_DIR" rev-parse --path-format=absolute --git-common-dir)")}
MAIN=$(cd "$MAIN" && pwd) || { echo "round.sh: error: ROUND_MAIN not a directory" >&2; exit 1; }
export ROUND_MAIN=$MAIN
BASE=${ROUND_BASE:-match-round-1}
WT_ROOT=$MAIN/.claude/worktrees
PY=$MAIN/.venv/bin/python3
HELPER=$SCRIPT_DIR/round_prompts.py
IF1_RE='^\+[[:space:]]*#[[:space:]]*if[[:space:]]+1([^0-9A-Za-z_]|$)'

say()  { printf '\n== %s\n' "$*"; }
info() { printf '   %s\n' "$*"; }
die()  { printf 'round.sh: error: %s\n' "$*" >&2; exit 1; }
run()  { printf '   $ %s\n' "$*"; "$@"; }
g()    { git -C "$MAIN" "$@"; }

ORIG_PWD=$PWD
cd "$MAIN" || die "cannot cd to $MAIN"
g rev-parse --verify -q "$BASE^{commit}" >/dev/null || die "base branch '$BASE' does not exist (ROUND_BASE)"

require_clean_main() {
    local dirty
    dirty=$(g status --porcelain --untracked-files=no)
    if [ -n "$dirty" ]; then
        printf '%s\n' "$dirty" >&2
        die "main checkout has uncommitted tracked changes (above); commit or stash them first"
    fi
}

# Agent worktrees: "path<TAB>head" for every registered worktree under .claude/worktrees/.
list_worktrees() {
    g worktree list --porcelain | awk -v root="$WT_ROOT/" '
        /^worktree /{p=substr($0,10)} /^HEAD /{h=$2}
        /^$/{ if (index(p, root)==1) print p "\t" h; p=""; h="" }
        END{ if (p != "" && index(p, root)==1) print p "\t" h }'
}

wt_registered() { list_worktrees | cut -f1 | grep -qxF "$1"; }

wt_dirty() { git -C "$1" status --porcelain --untracked-files=no; }

build_rom() {  # build_rom <logfile>; returns 0 iff the ROM checksum line says OK
    local log=$1
    say "full build (log: $log)"
    info "\$ make -j8 PYTHON=$MAIN/.venv/bin/python3"
    env PATH="$MAIN/.venv/bin:$HOME/local/bin:$PATH" make -j8 PYTHON="$MAIN/.venv/bin/python3" >"$log" 2>&1
    if grep -q 'build/pokestadium-us.z64: OK' "$log"; then
        info "build/pokestadium-us.z64: OK"
        return 0
    fi
    info "BUILD FAILED or ROM mismatch. Error lines (cfe warnings dropped), then the last 6 lines:"
    grep -E '[Ee]rror|FAILED|did NOT match|undefined reference' "$log" | grep -v 'cfe: Warning' | tail -20 | sed 's/^/   | /'
    info "..."
    tail -6 "$log" | sed 's/^/   | /'
    info "full log: $log"
    return 1
}

report_progress() {
    say "progress"
    info "GLOBAL_ASM lines in src: $(grep -rn GLOBAL_ASM src | wc -l)"
    info "$("$PY" progress.py -v us 2>/dev/null | grep '^all')"
}

# ---------------------------------------------------------------- start
DIGEST=$SCRIPT_DIR/digest.py
digests_enabled() { [ "${ROUND_DIGEST:-1}" != 0 ] && [ -f "$DIGEST" ]; }

# digest_one <agent> <worktree> <func> <src> <score>: runs in the background; never fails start.
digest_one() {
    local agent=$1 wt=$2 func=$3 src=$4 score=$5 log rc t0
    log=$wt/scratch_agent/digest_$func.log
    local args=("$func" --src "$src" --repo "$wt" --out "$wt/DIGEST_$func.md")
    [ "${ROUND_DIGEST_FULL:-0}" = 1 ] || args+=(--fast)
    [ -n "$score" ] && args+=(--score "$score")
    t0=$SECONDS
    "$PY" "$DIGEST" "${args[@]}" >"$log" 2>&1
    rc=$?
    if [ $rc -eq 0 ] && [ -s "$wt/DIGEST_$func.md" ]; then
        info "$agent: wrote DIGEST_$func.md ($(wc -l <"$wt/DIGEST_$func.md") lines, $((SECONDS - t0)) s)"
    else
        info "WARNING: $agent: digest.py failed for $func (exit $rc, log $log); the agent will run the oracles by hand"
    fi
}

# start_digests <agent> <worktree> SPEC...: one background digest per function, at most
# $ROUND_DIGEST_JOBS running at once.
start_digests() {
    local agent=$1 wt=$2 spec func src score
    shift 2
    for spec in "$@"; do
        func=${spec%%:*}; src=${spec#*:}; score=
        case $func in *@*) score=${func#*@}; func=${func%@*} ;; esac
        while [ "$(jobs -rp | wc -l)" -ge "${ROUND_DIGEST_JOBS:-4}" ]; do wait -n; done
        digest_one "$agent" "$wt" "$func" "$src" "$score" &
    done
}

cmd_start() {
    local force=0 file=""
    while [ $# -gt 0 ]; do
        case $1 in
            --force) force=1 ;;
            -h|--help) usage; exit 0 ;;
            -*) die "start: unknown option $1" ;;
            *) [ -z "$file" ] || die "start: only one assignments file"; file=$1 ;;
        esac
        shift
    done
    [ -n "$file" ] || die "start: missing <assignments-file>"
    case $file in /*) ;; *) file=$ORIG_PWD/$file ;; esac
    [ -f "$file" ] || die "start: no such file: $file"
    require_clean_main

    say "parsing $file"
    local parsed
    parsed=$("$PY" "$HELPER" parse "$file") || die "start: invalid assignments file"
    printf '%s\n' "$parsed" | sed 's/^/   /'

    # Check every target first so a refusal leaves nothing half-created.
    local agent specs wt
    while IFS=$'\t' read -r agent specs; do
        wt=$WT_ROOT/$agent
        if wt_registered "$wt" || [ -e "$wt" ]; then
            if [ $force -eq 0 ]; then
                die "worktree $wt already exists (use --force to remove and recreate it, or 'finish --remove-worktrees')"
            fi
        fi
    done <<<"$parsed"

    mkdir -p "$WT_ROOT"
    while IFS=$'\t' read -r agent specs; do
        wt=$WT_ROOT/$agent
        say "$agent: $specs"
        if wt_registered "$wt" || [ -e "$wt" ]; then
            if wt_registered "$wt"; then
                local ahead
                ahead=$(git -C "$wt" rev-list --count "$BASE..HEAD" 2>/dev/null || echo '?')
                info "--force: removing existing worktree ($ahead commits ahead of $BASE will be dropped)"
                run git worktree remove --force "$wt" || die "could not remove $wt"
            else
                die "$wt exists but is not a registered worktree; remove it by hand"
            fi
            run git worktree prune
        fi
        run git worktree add --detach "$wt" "$BASE" || die "git worktree add failed for $agent"
        run bash "$SCRIPT_DIR/agent_setup.sh" "$wt" || die "agent_setup.sh failed for $agent"
        # agent_setup.sh resets to match-round-1; honour a different ROUND_BASE.
        if [ "$(git -C "$wt" rev-parse HEAD)" != "$(g rev-parse "$BASE")" ]; then
            run git -C "$wt" reset --hard "$BASE"
        fi
        run mkdir -p "$wt/scratch_agent"
        local dflag=()
        digests_enabled && dflag=(--digests)
        # shellcheck disable=SC2086
        "$PY" "$HELPER" prompt --agent "$agent" --worktree "$wt" --main "$MAIN" --base "$BASE" "${dflag[@]}" $specs \
            >"$wt/PROMPT.md" || die "prompt generation failed for $agent"
        info "wrote $wt/PROMPT.md ($(wc -l <"$wt/PROMPT.md") lines)"
        info "HEAD: $(git -C "$wt" log --oneline -1)"
        if digests_enabled; then
            info "digests: started in the background ($( [ "${ROUND_DIGEST_FULL:-0}" = 1 ] && echo full || echo --fast))"
            # shellcheck disable=SC2086
            start_digests "$agent" "$wt" $specs
        fi
    done <<<"$parsed"
    if digests_enabled; then
        say "waiting for the oracle digests"
        wait
    fi
    say "done. Launch each agent in its worktree with PROMPT.md as the prompt, e.g."
    info "cd $WT_ROOT/<agent-k> && claude --model claude-opus-5-5 \"\$(cat PROMPT.md)\""
}

# ---------------------------------------------------------------- status
cmd_status() {
    local wts path head
    wts=$(list_worktrees)
    if [ -z "$wts" ]; then say "no agent worktrees under $WT_ROOT"; return 0; fi
    while IFS=$'\t' read -r path head; do
        say "$(basename "$path")  ($path)"
        info "HEAD: $(git -C "$path" log --oneline -1 HEAD)"
        local log n dirty if1
        log=$(git -C "$path" log --oneline "$BASE..HEAD")
        n=$(git -C "$path" rev-list --count "$BASE..HEAD")
        info "commits ahead of $BASE: $n"
        [ -n "$log" ] && printf '%s\n' "$log" | sed 's/^/     /'
        dirty=$(wt_dirty "$path")
        if [ -n "$dirty" ]; then info "modified tracked files:"; printf '%s\n' "$dirty" | sed 's/^/     /'
        else info "modified tracked files: none"; fi
        if1=$(git -C "$path" diff "$BASE..HEAD" -- src | grep -cE "$IF1_RE")
        if [ "$if1" -gt 0 ]; then info "COMMITTED '#if 1' lines under src: $if1  <-- must be fixed before integrating"
        else info "committed '#if 1' under src: none"; fi
    done <<<"$wts"
}

# ---------------------------------------------------------------- integrate
cmd_integrate() {
    [ $# -ge 1 ] || die "integrate: missing <agent-k>"
    local agent=$1; shift
    local wt=$WT_ROOT/$agent
    wt_registered "$wt" || die "integrate: no worktree $wt"
    local cur
    cur=$(g symbolic-ref -q --short HEAD) || die "integrate: main checkout is on a detached HEAD; check out $BASE first"
    [ "$cur" = "$BASE" ] || die "integrate: main checkout is on '$cur', not '$BASE' (git checkout $BASE, or set ROUND_BASE)"
    [ -e "$(g rev-parse --git-path CHERRY_PICK_HEAD)" ] && die "integrate: a cherry-pick is already in progress in the main checkout"
    require_clean_main

    local hashes=() h
    if [ $# -gt 0 ]; then
        local full
        for h in "$@"; do
            full=$(git -C "$wt" rev-parse --verify -q "$h^{commit}") || die "integrate: unknown commit $h"
            hashes+=("$full")
        done
        say "integrating $agent: ${#hashes[@]} commit(s) as given"
    else
        mapfile -t hashes < <(git -C "$wt" rev-list --reverse "$BASE..HEAD")
        say "integrating $agent: all ${#hashes[@]} commit(s) in $BASE..HEAD, oldest first"
    fi
    [ ${#hashes[@]} -gt 0 ] || { info "nothing to integrate"; return 0; }

    # Patch-ids already present in BASE (from an earlier integrate run) -> skip.
    local applied
    applied=$(git -C "$wt" cherry "$BASE" HEAD | awk '$1=="-"{print $2}')
    local before picked=0 skipped=0
    before=$(g rev-parse HEAD)
    for h in "${hashes[@]}"; do
        local subj
        subj=$(g log -1 --format='%h %s' "$h")
        if [ "$(g rev-list --parents -n1 "$h" | wc -w)" -gt 2 ]; then
            die "integrate: $subj is a merge commit; pick its parents by hand"
        fi
        if printf '%s\n' "$applied" | grep -qx "$h"; then
            info "skip (already in $BASE): $subj"; skipped=$((skipped + 1)); continue
        fi
        local n_if1
        n_if1=$(g show --format= "$h" -- src include | grep -cE "$IF1_RE")
        if [ "$n_if1" -gt 0 ]; then
            g show --format= "$h" -- src include | grep -nE "$IF1_RE" | sed 's/^/   | /'
            die "integrate: $subj adds $n_if1 '#if 1' line(s); not picked. $picked commit(s) picked so far (kept)."
        fi
        if ! run git cherry-pick "$h"; then
            if [ -z "$(g ls-files -u)" ] && g diff --cached --quiet; then
                info "empty cherry-pick (change already present); skipping"
                run git cherry-pick --skip; skipped=$((skipped + 1)); continue
            fi
            run git cherry-pick --abort
            die "integrate: CONFLICT picking $subj (aborted; $picked earlier pick(s) kept on $BASE).
  Likely cause: it depends on a commit that is not being picked. Re-run without hashes to take the
  whole $BASE..HEAD range, or resolve by hand."
        fi
        picked=$((picked + 1))
    done
    info "picked $picked, skipped $skipped"

    local log
    log=$(mktemp "${TMPDIR:-/tmp}/round_build.XXXXXX")
    if ! build_rom "$log"; then
        die "integrate: build is not OK after the picks (log $log). Nothing was reset; HEAD is $(g log --oneline -1).
  Commits picked by this run: $(g log --format=%h --reverse "$before..HEAD" | tr '\n' ' ')
  To undo: git reset --hard $before   (integrator's decision)"
    fi
    rm -f "$log"
    report_progress

    say "newly matched functions (GLOBAL_ASM lines removed by these picks)"
    local removed added
    removed=$(g diff "$before" HEAD -- src | grep -E '^-#pragma GLOBAL_ASM' | grep -oE 'func_[0-9A-Fa-f]{8}' | sort -u)
    added=$(g diff "$before" HEAD -- src | grep -E '^\+#pragma GLOBAL_ASM' | grep -oE 'func_[0-9A-Fa-f]{8}' | sort -u)
    # a moved GLOBAL_ASM line shows as both removed and added; only report the net change
    local f
    for f in $removed; do printf '%s\n' "$added" | grep -qx "$f" || info "$f"; done
    [ -n "$removed" ] || info "(none)"
    for f in $added; do printf '%s\n' "$removed" | grep -qx "$f" || info "WARNING: GLOBAL_ASM added back for $f"; done
    info "commits: $(g log --format=%h --reverse "$before..HEAD" | tr '\n' ' ')"
    info "write the NOTES.md entries; do NOT delete .s files until 'finish'"
}

# ---------------------------------------------------------------- finish
cmd_finish() {
    local remove=0 prefix=parked force=0
    while [ $# -gt 0 ]; do
        case $1 in
            --remove-worktrees) remove=1 ;;
            --park) [ $# -ge 2 ] || die "finish: --park needs a prefix"; prefix=$2; shift ;;
            --force) force=1 ;;
            -h|--help) usage; exit 0 ;;
            *) die "finish: unknown argument $1" ;;
        esac
        shift
    done

    local wts path head failed=0
    wts=$(list_worktrees)
    if [ $remove -eq 1 ] && [ -n "$wts" ]; then
        say "removing agent worktrees (unmerged work parked as $prefix-agent-k)"
        while IFS=$'\t' read -r path head; do
            local agent n br
            agent=$(basename "$path")
            if [ -n "$(wt_dirty "$path")" ] && [ $force -eq 0 ]; then
                info "SKIP $agent: has modified tracked files (commit them, or use --force to discard):"
                wt_dirty "$path" | sed 's/^/     /'
                failed=1; continue
            fi
            n=$(git -C "$path" rev-list --count "$BASE..HEAD")
            if [ "$n" -gt 0 ]; then
                br=$prefix-$agent
                local unmerged
                unmerged=$(git -C "$path" cherry "$BASE" HEAD | grep -c '^+')
                if g rev-parse --verify -q "refs/heads/$br" >/dev/null; then
                    if [ "$(g rev-parse "$br")" = "$head" ]; then
                        info "$br already at $head"
                    elif [ $force -eq 1 ]; then
                        run git branch -f "$br" "$head"
                    else
                        info "SKIP $agent: branch $br exists at another commit (use --force or another --park prefix)"
                        failed=1; continue
                    fi
                else
                    run git branch "$br" "$head"
                fi
                info "$agent: $n commit(s) ahead of $BASE ($unmerged not yet in $BASE by patch) parked on $br"
            else
                info "$agent: no commits ahead of $BASE; nothing to park"
            fi
            run git worktree remove --force "$path" || { failed=1; continue; }
        done <<<"$wts"
        run git worktree prune
    fi

    say "stale asm/us/nonmatchings .s files"
    wts=$(list_worktrees)
    if [ -n "$wts" ] && [ $force -eq 0 ]; then
        info "SKIPPED: $(printf '%s\n' "$wts" | wc -l) agent worktree(s) still exist and share asm/ by symlink;"
        info "deleting .s files now would break their builds. Use --remove-worktrees first, or --force."
    else
        local refs stale=0 s
        refs=$(grep -rhoE 'GLOBAL_ASM\("asm/us/nonmatchings/[^"]+\.s"\)' src | sed -E 's/^GLOBAL_ASM\("//; s/"\)$//' | sort -u)
        while IFS= read -r s; do
            if ! printf '%s\n' "$refs" | grep -qxF "$s"; then
                run rm -f "$s"; stale=$((stale + 1))
            fi
        done < <(find asm/us/nonmatchings -name '*.s' 2>/dev/null | sort)
        info "$stale stale file(s) deleted; $(find asm/us/nonmatchings -name '*.s' | wc -l) .s left, $(printf '%s\n' "$refs" | grep -c .) referenced"
    fi

    local log
    log=$(mktemp "${TMPDIR:-/tmp}/round_build.XXXXXX")
    if build_rom "$log"; then rm -f "$log"; else failed=1; fi
    report_progress
    if [ -f "$MAIN/matching_notes/corpus.py" ]; then
        say "refreshing the corpus index"
        run "$PY" "$MAIN/matching_notes/corpus.py" build || failed=1
    fi
    say "worktrees now:"; g worktree list | sed 's/^/   /'
    [ $failed -eq 0 ] || die "finish: some steps were skipped or failed (see above)"
}

# ---------------------------------------------------------------- farm-list
cmd_farm_list() {
    "$PY" "$HELPER" open "$@"
}

# ---------------------------------------------------------------- dispatch
[ $# -ge 1 ] || { usage; exit 1; }
cmd=$1; shift
case $cmd in
    start) cmd_start "$@" ;;
    status) cmd_status "$@" ;;
    integrate) cmd_integrate "$@" ;;
    finish) cmd_finish "$@" ;;
    farm-list) cmd_farm_list "$@" ;;
    -h|--help|help) usage ;;
    *) usage >&2; die "unknown command '$cmd'" ;;
esac
