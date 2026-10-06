#!/bin/bash
# One-time setup for a matching-agent worktree. Usage: agent_setup.sh <worktree-dir>
# Resets the worktree to match-round-1 and links/copies the gitignored build inputs
# (baserom, .venv, asm, permuter, yaml) plus a private copy of build/.
set -e
MAIN=/mnt/b410f78a-9927-453b-b3b6-4b3910634741/Code/pokestadium
cd "$1"
git reset --hard match-round-1
echo "HEAD is now:"; git log --oneline -1
ln -s "$MAIN/.venv" .venv
ln -s "$MAIN/asm" asm
ln -s "$MAIN/tools/permuter" tools/permuter
ln -s "$MAIN/pokestadium-us.yaml" poketadium-us.yaml
ln -s "$MAIN/baseroms/us/baserom.z64" baseroms/us/baserom.z64
ln -s "$MAIN/expected" expected
cp -r "$MAIN/build" build
find build -exec touch {} +
echo "setup done in $PWD"
