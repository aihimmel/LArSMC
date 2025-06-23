#!/usr/bin/env bash
set -euo pipefail

IMG=/cvmfs/singularity.opensciencegrid.org/fermilab/fnal-dev-sl7:latest
BINDS=/cvmfs,/exp,/nashome,/pnfs/dune,/opt,/run/user,/etc/hostname,/etc/hosts,/etc/krb5.conf

apptainer exec --ipc --pid -B "$BINDS" --pwd "$PWD" "$IMG" bash -lc "source $(dirname "$0")/setup_lars.sh && ninja $*"
