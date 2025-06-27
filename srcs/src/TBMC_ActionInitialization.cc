#include "TBMC_ActionInitialization.hh"
#include "TBMC_EventAction.hh"
#include "TBMC_PrimaryGeneratorAction.hh"
#include "TBMC_RunAction.hh"
#include "TBMC_SteppingAction.hh"
#include "TBMC_TrackingAction.hh"

TBMC_ActionInitialization::TBMC_ActionInitialization()
  : G4VUserActionInitialization()
{}

TBMC_ActionInitialization::~TBMC_ActionInitialization() {}

void TBMC_ActionInitialization::BuildForMaster() const
{
    SetUserAction(new TBMC_RunAction());
}

void TBMC_ActionInitialization::Build() const
{
    TBMC_PrimaryGeneratorAction* primary = new TBMC_PrimaryGeneratorAction();
    SetUserAction(primary);
    SetUserAction(new TBMC_RunAction(primary));
    TBMC_EventAction* event = new TBMC_EventAction();
    SetUserAction(event);
    SetUserAction(new TBMC_SteppingAction(event));
    TBMC_TrackingAction* track = new TBMC_TrackingAction();
    SetUserAction(track);
}
