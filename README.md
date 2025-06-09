### LArSMC -- Simulation of the LArS experiment in TallBo using Geant4

----------------------------------------------------------------------

  *Maintainer*:               A. Himmel  <ahimmel@fnal.gov>
  
  *Authors*:                  W. Mu, L. Zhao, W. Castiglioni, F. Yu
  
  *Last update to this document*:  February 2024

----------------------------------------------------------------------



### How to Run (on a dunegpvm)

First, you need to start up an SL7 container:
```
/cvmfs/oasis.opensciencegrid.org/mis/apptainer/current/bin/apptainer shell --shell=/bin/bash \
-B /cvmfs,/exp,/nashome,/pnfs/dune,/opt,/run/user,/etc/hostname,/etc/hosts,/etc/krb5.conf --ipc --pid \
/cvmfs/singularity.opensciencegrid.org/fermilab/fnal-dev-sl7:latest
```

Then, inside the container, run the following setup:
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

cd <build directory> # Suggest placing outside the repo directory
cmake -DGeant4_DIR=$G4DIR <repo>/srcs -DGEANT4_INSTALL_DATA=ON -DGEANT4_USE_OPENGL_X11=ON
 
make clean ; make -j 8
 
./TBMC -g <repo>/srcs/gdml/lars_tallbo_true.gdml -m ./vis.mac -o larsmc_90cm.root | tee log_90cm.txt
```

### How to visualize a geometry

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

Get the environment for submission set up:
```
/cvmfs/dune.opensciencegrid.org/products/dune/justin/justin-sl7-setup
source /cvmfs/dune.opensciencegrid.org/products/dune/setup_dune.sh
setup python  v3_9_15          # ≥3.8 avoids the unlink() issue
setup justin
justin time
justin get-token
```

Next, upload the build directory to the RCDS service so the executable can be accessed on the grid node:

```
INPUT_TAR_DIR=$(<repo>/justin/rcds_prep.sh <build directory>)
```

