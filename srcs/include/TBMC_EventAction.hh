#ifndef TBMC_EventAction_h
#define TBMC_EventAction_h 1

#include "globals.hh"
#include "G4UserEventAction.hh"
#include "TBMC_Analysis.hh"

class TBMC_EventAction : public G4UserEventAction
{
public:
    TBMC_EventAction();
    ~TBMC_EventAction();
    
    void BeginOfEventAction(const G4Event*) override;
    void EndOfEventAction(const G4Event*) override;
    
    void AddRayleigh() { ++fRayleigh; }
    void AddAbsorption() { ++fAbsorption; }
    void AddBoundary() { ++fBoundary; }

private:
    G4int fRayleigh;
    G4int fAbsorption;
    G4int fBoundary;
    
    TBMC_Analysis*  fAna;
};
#endif
