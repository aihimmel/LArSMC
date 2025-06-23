#!/usr/bin/env bash
# -- Environment that cmake/ninja need ------------------------------
export UPS_OVERRIDE="-H Linux64bit+3.10-2.17"
source /cvmfs/dune.opensciencegrid.org/products/dune/setup_dune.sh > /dev/null
setup -B geant4 v4_10_6_p01c   -q +e20:prof
setup -B root   v6_20_08a      -q +e20:p383b:prof
setup -B cmake  v3_19_6
export CXX=$(which g++)
export CC=$(which gcc)
export G4INSTALL=/cvmfs/larsoft.opensciencegrid.org/products/geant4/v4_10_6_p01/Linux64bit+2.6-2.12-e19-prof
export G4DIR=$G4INSTALL/lib64
