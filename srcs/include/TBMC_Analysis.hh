#ifndef _TBMC_ANALYSIS_
#define _TBMC_ANALYSIS_ 1

#include "globals.hh"
#include "G4Run.hh"
#include "G4ThreeVector.hh"

#include "TFile.h"
#include "TTree.h"

#include <vector>

using namespace std;

class TBMC_Analysis 
{
private:
    static TBMC_Analysis* fInstance;  
    TFile* fOutputFile;
    TTree* fEventTree;
    TTree* fTrackTree;

public:
    TBMC_Analysis();
    ~TBMC_Analysis();
    static G4String fFilename;
    static TBMC_Analysis* getInstance();
  
    void BeginOfRun();
    void EndOfRun();
    void BeginOfEvent();
    void EndOfEvent();
    void BeginOfTrack();
    void EndOfTrack();
    void Reset();
    void bookTree();
  
    std::string fProcessName;

    // G4int StepTracker;
    // G4int StepTracker2;

    G4double init_x;
    G4double init_y;
    G4double init_z;
    G4double init_energy;

    G4double fin_x;
    G4double fin_y;
    G4double fin_z;
    G4double fin_r_squared;     // This is the r^2 value from the reference point (8.75, 0) in cm
    G4double fin_volume;
    // G4int fin_volume_status;    // Used in Stepping Action to tell us if the photon was absorbed in the border surface
       
    G4int fopDetID;
    G4int fnAbsorb;
    G4int fnRayleigh;
    
    G4double fStepLength;
    G4double fabsLengthLAr;     // Predefined value, absorption length of VUV light in LAr
    G4double fRayleighLength;   // Manually give rayleigh length to vuv photons. Rayleigh length for visible photons is calculated according to theo.
    G4double fLArLevel;         // Predefined value, liquid level, in cm, above the upper edge of WLS' upper edge
};
#endif
