Continue the Pokemon Stadium (US) decomp rename+reorg to michiiik convergence. Repo:
~/Code/pokestadium, branch match-round-1 (local only, never push without asking).
We're on Palmetto; builds gate through the wave drivers; the OTHER SESSION (matching/
farm) may be active - coordinate via matching_notes/CROSS_SESSION_CHANNEL.md and never
sweep its uncommitted work (drivers scope their git adds).

Read matching_notes/RENAME_PLAN.md BOTTOM-UP ("CURRENT STATE" first), then
hippo_name_conflicts.md + rename_parked.md. The target tree is michiiik/pokestadium
(Team Hippodrome) - pret is DEAD as a target. Then:
1. Check scratch/rename_waves/driver_statics.log for the running/finished statics
   waves; launch waves 7-13 with the same command if the tail remains.
2. Michiiik toolchain pin: get their build working (ask them / their ci config), then
   the statics address-join (recipe in RENAME_PLAN).
3. Reorg residuals (groups 5/6/7/8/61, 1/31/77, main segment, un-joined yaml entries).
4. Keep PLAN/RENAME_PLAN and the ledger updated; commit your own work before waves.
