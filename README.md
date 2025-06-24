### LArSMC -- Simulation of the LArS experiment in TallBo using Geant4

----------------------------------------------------------------------

  *Maintainer*:               A. Himmel  <ahimmel@fnal.gov>
  
  *Authors*:                  A. Breaux, W. Mu, L. Zhao, W. Castiglioni, F. Yu
  
  *Last update to this document*:  June 2025

----------------------------------------------------------------------



### How to Build and Run (on a dunegpvm)

First, you need to start up an SL7 container:
```
/cvmfs/oasis.opensciencegrid.org/mis/apptainer/current/bin/apptainer shell --shell=/bin/bash \
-B /cvmfs,/exp,/nashome,/pnfs/dune,/opt,/run/user,/etc/hostname,/etc/hosts,/etc/krb5.conf --ipc --pid \
/cvmfs/singularity.opensciencegrid.org/fermilab/fnal-dev-sl7:latest
```

This is the required environment setup, it has now been captured in the `setup_lars.sh` script.
```
export UPS_OVERRIDE="-H Linux64bit+3.10-2.17"
source /cvmfs/dune.opensciencegrid.org/products/dune/setup_dune.sh
setup -B geant4 v4_10_6_p01c -q+e20:prof
setup -B root v6_20_08a -q+e20:p383b:prof
setup -B cmake v3_19_6
export CXX=`which g++`
export CC=`which gcc`
export G4INSTALL=/cvmfs/larsoft.opensciencegrid.org/products/geant4/v4_10_6_p01/Linux64bit+2.6-2.12-e19-prof
export G4DIR=$G4INSTALL/lib64
```

Then, inside the container, run the following setup:
```
export LARS=<repo>
export BUILD=$LARS/../larsmc-build

# Configure
cd $BUILD # Suggest placing outside the repo directory
cmake -DGeant4_DIR=$G4DIR $LARS/srcs -DGEANT4_INSTALL_DATA=ON -DGEANT4_USE_OPENGL_X11=ON -g Ninja
 
# Build
ninja -j 8

# Run example
./TBMC -g ./gdml/lars_tallbo_true.gdml -m ./vis.mac -o larsmc_90cm.root | tee log_90cm.txt
```

Alternatively, the scripts `cmake_in_container.sh` and `ninja_in_container.sh` automate the configuring and building inside the container. Here's how that would look:

```
export LARS=<repo>
export BUILD=$LARS/../larsmc-build
$LARS/scripts/cmake_in_container.sh -DGeant4_DIR=$ENV{G4DIR} -DGEANT4_INSTALL_DATA=ON -DGEANT4_USE_OPENGL_X11=ON --no-warn-unused-cli -S$LARS/srcs -B$BUILD -G Ninja
cd $BUILD # Suggest placing outside the repo directory
$LARS/scripts/ninja_in_container.sh

./TBMC -g ./gdml/lars_tallbo_true.gdml -m ./vis.mac -o larsmc_90cm.root | tee log_90cm.txt
```


### How to visualize a geometry

Here's how to do it in root, but it doesn't work with our GDML files since they use loops.
```
std::string testfile = "simple.gdml"
gSystem->Load("libGeom");
gSystem->Load("libGdml");
TGeoManager::Import(testfile.c_str());
gGeoManager->GetTopVolume()->Draw("ogl");
```

### How to submit via justIN

(WORK IN PROGRESS!)

Link to the general justiN documentation: https://justin.dune.hep.ac.uk/docs/overview.md

Get the environment for submission set up -- note this is _not_ inside the SL7 container
```
source /cvmfs/larsoft.opensciencegrid.org/spack-packages/setup-env.sh
spack load justin
justin time
justin get-token
```

Next, upload the build directory to the RCDS service so the executable can be accessed on the grid node. You may need to wait a few minutes for the files to be visible in CVMFS.
```
INPUT_TAR_DIR=$($LARS/justin/rcds_prep.sh $BUILD)
export INPUT_TAR_DIR
ls $INPUT_TAR_DIR
```

You can run a local test by doing the following:
```
justin-test-jobscript --monte-carlo 1 \
                      --jobscript lars_mc_onepergdml.jobscript \
                      --env INPUT_TAR_DIR="$INPUT_TAR_DIR" \
                      --scope usertests
```


To actually submit to the grid, do:
```
justin simple-workflow --image fnal-wn-sl7:latest  \
                       --name larsmc-test-$(date +%Y%m%d%H%M) \
                       --monte-carlo 6 \
                       --jobscript lars_mc_onepergdml.jobscript \
                       --env INPUT_TAR_DIR=$INPUT_TAR_DIR \
                       --scope usertests \
                       --output-pattern "larsmc_*.root:$USERURL/$USER/justin" \
                       --output-pattern "otherfiles_*.tgz:$USERURL/$USER/justin" # Remove if you only care about the MC output            
```
or, run
```
scripts/justin_submission_example.sh
```
