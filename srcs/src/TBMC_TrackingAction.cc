#include "TBMC_TrackingAction.hh"
#include "TBMC_Analysis.hh"

#include "G4Track.hh"
#include "G4ThreeVector.hh"

#include "globals.hh"
#include "G4SystemOfUnits.hh"

TBMC_TrackingAction::TBMC_TrackingAction() : G4UserTrackingAction()
{
    fAna = TBMC_Analysis::getInstance();
}

TBMC_TrackingAction::~TBMC_TrackingAction() 
{}

void TBMC_TrackingAction::PreUserTrackingAction (const G4Track* track)
{
    G4ThreeVector init_pos = track->GetVertexPosition();

    fAna->init_x = init_pos.x();
    fAna->init_y = init_pos.y();
    fAna->init_z = init_pos.z();
    fAna->init_energy = track->GetVertexKineticEnergy();

    fAna->BeginOfTrack();
}

// void TBMC_TrackingAction::PostUserTrackingAction (const G4Track* track)    // Not needed yet.