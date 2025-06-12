#!/usr/bin/env bash
# Build a flat tar from a LArSMC build and upload it with RCDS.
# Prints the resulting CVMFS directory on stdout.

set -euo pipefail
BUILD_DIR=${1:-/exp/dune/app/users/ahimmel/LArS/larsmc-build}
STAMP=$(date +%Y%m%d_%H%M)
TAR=/tmp/larsmc_rcd_${STAMP}.tar   # must be .tar, *not* .tar.gz

[[ -d $BUILD_DIR ]] || { echo "ERROR: $BUILD_DIR not found" >&2; exit 1; }

# --- create flat tar (tutorial requires no parent directory) -----------------
cd "$BUILD_DIR"
tar cf "$TAR" *                                    # flat payload  :contentReference[oaicite:7]{index=7}

# --- Check that justin has been initialized ---------------------------------
if ! command -v justin &> /dev/null; then
    echo "ERROR: justin command not found. Please initialize justin first." >&2
    exit 1
fi

# --- Get a token for justin-cvmfs-upload ----------------------------------------
justin get-token || { echo "ERROR: could not get token" >&2; exit 1; }

# --- upload; requires that you already ran justin get-token -------------------
INPUT_TAR_DIR=$(justin-cvmfs-upload "$TAR")        # waits for unpack  :contentReference[oaicite:8]{index=8}

echo "$INPUT_TAR_DIR"
