SETUP (do this first, exactly once; W = the directory `pwd` prints when you start, a git worktree
under /home/tsranso/Code/pokestadium/.claude/worktrees/. Never edit files in the main repo.)
1. `pwd` -> W.
2. `MAIN=/home/tsranso/Code/pokestadium bash /home/tsranso/Code/pokestadium/matching_notes/agent_setup.sh W`
   (resets W to match-round-1, links .venv/baserom/expected/permuter, copies build/).
3. Replace the shared asm link with a private copy so the integrator can regenerate the main repo's asm
   tonight without breaking your builds: `rm W/asm` (removes only the symlink, nothing under it), then
   `cp -r /home/tsranso/Code/pokestadium/asm W/asm`.
4. `mkdir -p W/scratch_agent` (your notes/specs; never commit it: always `git commit -am`, never `git add -A`).
5. Sanity: in W, `env PATH=W/.venv/bin:/home/tsranso/local/bin:$PATH make -j2 PYTHON=W/.venv/bin/python3`
   must end with `build/pokestadium-us.z64: OK`.
The node has 8 cores shared by 8 agents: never use more than `make -j2`; prefer fd.sh/var.py (one object).
The integrator gives you a deadline; commit whatever you have (draft improvements + `//` notes) before it.

LESSONS FROM ROUND 8 (2026-10-16), also in IDO_TRICKS.md:
- IDO places .data in source order, INCLUDING initialized function-local statics (`static s32 x = 0;`
  goes to .data at its source position; without an initializer it goes to .bss). This matched
  func_81207DF8: a "needs an in-function static" draft is now solvable by defining the static with an
  initializer and moving the file's later data definitions below the function.
- Several data blobs are now C (datamig.py). Data symbols that were asm may now be real C definitions in
  the owner file; read the file's current data before assuming layouts.
- matching_notes/try_candidate.py src/<file>.c func_X <candidate source.c> splices a permuter candidate
  into the draft and runs fd.sh (restores the file).
- fd.sh uses diff.py -s, which can give false zeros: a match counts only after the full make prints OK.

