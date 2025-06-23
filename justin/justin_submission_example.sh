#!/bin/bash

USERURL='https://fndcadoor.fnal.gov:2880/dune/scratch/users'

justin simple-workflow --image fnal-wn-sl7:latest  \
                       --name larsmc-test-$(date +%Y%m%d%H%M) \
                       --monte-carlo 6 \
                       --jobscript lars_mc_test.jobscript \
                       --env INPUT_TAR_DIR="$INPUT_TAR_DIR" \
                       --scope usertests \
                       --output-pattern "*.*:$USERURL/$USER"
