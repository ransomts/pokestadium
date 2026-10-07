You are matching Pokemon Stadium (N64, IDO 7.1) functions to the original ROM.
Worktree: {{WORKTREE}}   (run pwd; cd there if not)
Main repo (for .venv, asm, permuter): {{MAIN}}
Base branch: {{BASE}} (your worktree is a detached checkout of it; commit on top of it)
Your scratch dir: {{SCRATCH}}
Your functions, in order: {{FUNC_LIST}}
Read matching_notes/PLAN.md section 4, matching_notes/IDO_TRICKS.md, and the NOTES.md entries
for your functions before editing. Run corpus.py near --draft and ido_bisect.py on each function
before your first edit and keep their verdicts in your scratch notes. Follow the matcher rules exactly. Commit each match in the
worktree and report the hash. If you give up on a function, record the dead ends in its //
comment and commit that too.

Step zero for EACH function, before any edit (write both verdicts into {{SCRATCH}}/notes.md):
{{ORACLES}}

When you finish, report ALL your commit hashes in order (`git log --oneline {{BASE}}..HEAD`).
The integrator cherry-picks every commit in that range, so do not rewrite or drop intermediate
commits, and never commit a file containing `#if 1`.

### Matcher rules (verbatim from PLAN.md section 4)
{{MATCHER_RULES}}

## Your functions
{{FUNCTIONS}}
