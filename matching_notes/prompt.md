Continue the Pokemon Stadium (US) decomp to completion. Repo: ~/Code/pokestadium, branch
match-round-1 (local only, never push without asking me). We're on Palmetto: builds and gates
go through sbatch, agents run in Agent-tool worktrees.

Read matching_notes/PLAN.md section 0 (status table) first, then the "ROUND 10 PICKUP"
section at the very end of matching_notes/NOTES.md - it has the full state, the farm relaunch
command, and the F6 agent-wave recipe. Then matching_notes/IDO_TRICKS.md "SCORE TRUST RULES"
(full diff only; permuter numbers never ranked) and the uopt copy-propagation model at its end.

Then work through the roadmap:
1. F6 renames: continue the agent waves per the recipe in NOTES.md ROUND 10 PICKUP (rename_
   agent.py + rename_salvage.py + one rename.py apply gate per wave). ~5,700 referenced
   placeholders + Tier C struct fields remain. Respect the farm-merge closure in
   renames_protected.txt until the five open functions match.
2. Matching: the 5 open functions (scores in PLAN.md section 0; each draft's // comment has
   the model + dead ends). Relaunch the farm per the NOTES.md command when convenient; API
   limit resets Oct 19 7pm for Opus agents (worktrees agent-1..6 parked clean for resume).
3. F5 upstream: fold the rename commits into the up/* branch series, per UPSTREAM_PR_plan.md;
   STOP for owner approval before any push. Permuter sizeof PR per UPSTREAM_PR_permuter_sizeof.md.

Keep PLAN.md, NOTES.md and memory updated as you go. Ask me about the parked decisions if
anything is unclear (species-stats alias triple, undefined_syms.ld dual-source symbols).
