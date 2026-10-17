Continue the Pokemon Stadium (US) decomp to completion. Repo: ~/Code/pokestadium, branch
match-round-1 (local only, never push without asking me). We're on Palmetto: builds and gates go
through sbatch, agents run in Agent-tool worktrees.

Read matching_notes/PLAN.md first (sections 0, Finish roadmap, F2 and F5 detail, 4.3, and the round 8
process lessons), then the "Round 8" sections at the end of matching_notes/NOTES.md and the end of
matching_notes/IDO_TRICKS.md (the uopt copy-propagation model). Each open function's
#ifdef NON_MATCHING draft has a // comment with what still differs and the dead ends.

Then work through the roadmap:
1. F1 harvest: check farm jobs 17512644 (tag v) and 17512996 (tag w) and every
   /scratch/$USER/permuter_best/<func>* for the 6 open functions. Adopt any score-0 output with
   matching_notes/adopt_candidate.py; for near misses use try_candidate.py (score without -s) and
   carry plausible ideas into the drafts. Re-check asm/us/data/rom_rodata_7E0D0 with
   matching_notes/datamig.py now that 2 of the 3 GB APU functions match.
2. F2 round 9: launch one Opus agent per file group for the 6 open functions (prompt =
   matching_notes/round_setup.md + a short per-round paragraph + round_prompts.py output), plus a
   farm job re-seeded from the current drafts. Have agents use matching_notes/ccs.py to test uopt
   hypotheses. Integrate as results arrive: cherry-pick each agent's commits, full make must print
   OK, re-seed the farm when a draft improves.
3. F4: finish or document the leftover data files listed in PLAN.md.
4. F5: once the open functions are matched or stalled, prepare the upstream work (rebase onto
   origin/master, tidy permuter-formatted functions, split into PR branches) and stop for my
   approval before pushing anything.

Ask me about the parked decisions (gDisplayListHead alias pair, func_86A013C8 labels) when you
reach them. Keep PLAN.md, NOTES.md and memory updated as you go.
