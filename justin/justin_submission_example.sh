#!/bin/bash

USERURL='https://fndcadoor.fnal.gov:2880/dune/scratch/users'

# Check that INPUT_TAR_DIR is set
if [[ -z "${INPUT_TAR_DIR:-}" ]]; then
    echo "ERROR: INPUT_TAR_DIR environment variable is not set. Maybe you need to export it?" >&2
    exit 2
fi

justin simple-workflow --image fnal-wn-sl7:latest  \
                       --name larsmc-onepergdml-$(date +%Y%m%d%H%M) \
                       --monte-carlo 6 \
                       --jobscript lars_mc_onepergdml.jobscript \
                       --env INPUT_TAR_DIR=$INPUT_TAR_DIR \
                       --scope usertests \
                       --output-pattern "larsmc_*.root:$USERURL/$USER/justin" \
                       --output-pattern "otherfiles_*.tgz:$USERURL/$USER/justin" # Remove if you only care about the MC output
