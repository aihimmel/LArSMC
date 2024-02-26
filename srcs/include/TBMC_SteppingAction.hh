#ifndef TBMC_SteppingAction_h
#define TBMC_SteppingAction_h 1

#include "TBMC_EventAction.hh"
#include "globals.hh"
#include "G4UserSteppingAction.hh"
#include "TBMC_Analysis.hh"

class TBMC_SteppingAction : public G4UserSteppingAction
{
public:
    TBMC_SteppingAction(TBMC_EventAction*);
    ~TBMC_SteppingAction();
    
    void UserSteppingAction(const G4Step*) override;

private:
    TBMC_EventAction* fEventAction;
    TBMC_Analysis*  fAna;

    void scattProc_DoIt(const G4Step* step);
    void absProc_DoIt(const G4Step* step);
    void boundaryProc_DoIt(const G4Step* step);
    void opPhoton_DoIt(const G4Step* step);
    void stepVerboseInfo(const G4Step* step);
    
    G4int isParticle(const char* particleName,const G4Step* step);
    G4int isProcess(const char* processName,const G4Step* step);
    G4int isVolume(const char* volumeName,const G4Step* step);
    G4int isNextVolume(const char* nextVolumeName,const G4Step* step);
};
#endif
