#include "TBMC_EventAction.hh"
#include "TBMC_Run.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"

TBMC_EventAction::TBMC_EventAction()
: G4UserEventAction()
{
    fRayleigh   = 0;
    fAbsorption = 0;
    fBoundary   = 0;
  
    fAna = TBMC_Analysis::getInstance();
}

TBMC_EventAction::~TBMC_EventAction() {}

void TBMC_EventAction::BeginOfEventAction(const G4Event*)
{
    fRayleigh   = 0;
    fAbsorption = 0;
    fBoundary   = 0;
  
    fAna->BeginOfEvent();
}

void TBMC_EventAction::EndOfEventAction(const G4Event*)
{
    TBMC_Run* run = static_cast<TBMC_Run*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());
    run->AddRayleigh(fRayleigh);
    run->AddAbsorption(fAbsorption);
    run->AddBoundary(fBoundary);
    
    fAna->EndOfEvent();
}
