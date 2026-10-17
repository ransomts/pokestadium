#!/bin/bash
# One-time setup for a matching-agent worktree. Usage: agent_setup.sh <worktree-dir>
# Resets the worktree to match-round-1 and links/copies the gitignored build inputs
# (baserom, .venv, asm, permuter, yaml) plus a private copy of build/.
set -e
# MAIN = the main checkout (holds the gitignored inputs). Defaults to the checkout that owns
# this repo's .git, so it works from any clone/machine; override with MAIN=/path agent_setup.sh ...
MAIN=${MAIN:-$(dirname "$(git -C "$(dirname "$0")" rev-parse --path-format=absolute --git-common-dir)")}
cd "$1"
git reset --hard match-round-1
echo "HEAD is now:"; git log --oneline -1
ln -s "$MAIN/.venv" .venv
ln -s "$MAIN/asm" asm
ln -s "$MAIN/tools/permuter" tools/permuter
ln -s "$MAIN/pokestadium-us.yaml" pokestadium-us.yaml
ln -s "$MAIN/assets" assets
ln -s "$MAIN/baseroms/us/baserom.z64" baseroms/us/baserom.z64
ln -s "$MAIN/expected" expected
cp -r "$MAIN/build" build
find build -exec touch {} +
echo "setup done in $PWD"
