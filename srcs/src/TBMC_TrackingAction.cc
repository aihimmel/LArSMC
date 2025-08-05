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
    // fAna->fin_volume_status = 0;

    G4ThreeVector init_pos = track->GetVertexPosition();
    G4double init_energy = track->GetVertexKineticEnergy();

    fAna->init_x = init_pos.x();
    fAna->init_y = init_pos.y();
    fAna->init_z = init_pos.z();
    fAna->init_energy = init_energy;

    fAna->fin_volume = 0.;

    fAna->BeginOfTrack();
}

void TBMC_TrackingAction::PostUserTrackingAction (const G4Track* track)
{
    G4ThreeVector fin_pos = track->GetPosition();

    fAna->fin_x = fin_pos.x();
    fAna->fin_y = fin_pos.y();
    fAna->fin_z = fin_pos.z();
    fAna->fin_r_squared = ((fin_pos.x() - 87.5) * (fin_pos.x() - 87.5)) + (fin_pos.y() * fin_pos.y());

    if (fAna->fin_volume != 13.)
    {
        std::string final_volume_name = track->GetVolume()->GetName();

        if (final_volume_name == "volOpDet_0_PV") {fAna->fin_volume = 1.;} 
        else if (final_volume_name == "volOpDet_1_PV") {fAna->fin_volume = 2.;}
        else if (final_volume_name == "volOpDet_2_PV") {fAna->fin_volume = 3.;}
        else if (final_volume_name == "volOpDet_3_PV") {fAna->fin_volume = 4.;}
        else if (final_volume_name == "volOpDet_4_PV") {fAna->fin_volume = 5.;}
        else if (final_volume_name == "volOpDet_5_PV") {fAna->fin_volume = 6.;}
        else if (final_volume_name == "volOpDet_6_PV") {fAna->fin_volume = 7.;}
        else if (final_volume_name == "volOpDet_7_PV") {fAna->fin_volume = 8.;}
        else if (final_volume_name == "volOpDet_8_PV") {fAna->fin_volume = 9.;}
        else if (final_volume_name == "volOpDet_9_PV") {fAna->fin_volume = 10.;}
        else if (final_volume_name == "volLAr_PV") {fAna->fin_volume = 11.;}
        else if (final_volume_name == "volGAr_PV") {fAna->fin_volume = 12.;}
        else if (final_volume_name == "volCage_PV") {fAna->fin_volume = 13.;}
        else if (final_volume_name == "volTank_PV") {fAna->fin_volume = 14.;}
        else if (final_volume_name == "World_volume_PV") {fAna->fin_volume = 15.;}
        else {;}
    }

    fAna->EndOfTrack();

}