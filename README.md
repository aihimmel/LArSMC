### LArSMC -- Simulation of the LArS experiment in TallBo using Geant4

----------------------------------------------------------------------

  *Maintainer*:               A. Himmel  <ahimmel@fnal.gov>
  *Authors*:                  W. Mu, L. Zhao, W. Castiglioni, F. Yu
  
  *Last update to this document*:  February 2024

----------------------------------------------------------------------



### How to Run (on a dunegpvm)

```
source /grid/fermiapp/products/dune/setup_dune.sh
setup -B geant4 v4_10_6_p01c -q+e20:prof
setup -B root v6_20_08a -q+e20:p383b:prof
setup -B cmake v3_19_6
export CXX=`which g++`
export CC=`which gcc`
export G4INSTALL=/cvmfs/larsoft.opensciencegrid.org/products/geant4/v4_10_6_p01/Linux64bit+2.6-2.12-e19-prof
export G4DIR=$G4INSTALL/lib64
 
cd <build directory>
cmake -DGeant4_DIR=$G4DIR <repo>/srcs -DGEANT4_INSTALL_DATA=ON -DGEANT4_USE_OPENGL_X11=ON
 
make clean ; make -j 8
 
./TBMC -g ../srcs/gdml/lars_tallbo_true.gdml -m ./vis.mac -o larsmc_90cm.root | tee log_90cm.txt
```
