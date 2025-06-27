#include "TBMC_Analysis.hh"
#include "G4RunManager.hh"
#include "algorithm"

TBMC_Analysis* TBMC_Analysis::fInstance = 0;
G4String TBMC_Analysis::fFilename = "";

TBMC_Analysis::TBMC_Analysis()
{    
    fabsLengthLAr    = 10;
    fRayleighLength  = 10;
    fLArLevel        = 10;

    init_x = 0.;
    init_y = 0.;
    init_z = 0.;
    init_energy = 0.;
    
    fEventTree  = NULL;
    fTrackTree  = NULL;
    fOutputFile = NULL;

    bookTree();
}

TBMC_Analysis::~TBMC_Analysis()
{
    if(fOutputFile)
    {
        delete fOutputFile;
    }
}

TBMC_Analysis* TBMC_Analysis::getInstance()
{
    if(!fInstance)
    {
        fInstance = new TBMC_Analysis;
    }
    
    return fInstance;
}

void TBMC_Analysis::BeginOfRun()
{
    Reset();
    return; 
}

void TBMC_Analysis::EndOfRun()
{
    fEventTree->Write();
    fTrackTree->Write();

    fOutputFile->cd();
    fOutputFile->Close();

    return;
}

void TBMC_Analysis::BeginOfEvent()
{
    Reset();
    return;
}

void TBMC_Analysis::EndOfEvent()
{
    fEventTree->Fill();
    return;
}

void TBMC_Analysis::BeginOfTrack()
{
    fTrackTree->Fill();
    return;
}

void TBMC_Analysis::Reset()
{
   fabsLengthLAr    = 10;
   fRayleighLength  = 10;
   fLArLevel        = 10;
   fopDetID         = -1;
   fKillVolName     ="NULL";
   fnAbsorb         = 0;
   fnRayleigh       = 0;
   
   return;
}

void TBMC_Analysis::bookTree()
{
    G4cout<<"Booking tree .... "<<G4endl;
    if(!fOutputFile) fOutputFile = NULL;
    if(fFilename=="")
    {
        fFilename="./ana.root";
    }
    G4cout<<"Creating tree "<<fFilename<<G4endl;

    fOutputFile = new TFile(fFilename, "RECREATE");
    fEventTree  = new TTree("EventTree", "EventTree");
    fTrackTree  = new TTree("TrackTree", "TrackTree");

    fEventTree->Branch("KillVol",    &fKillVolName);
    fEventTree->Branch("Process",    &fProcessName);
    fEventTree->Branch("OpDet",      &fopDetID);
    fEventTree->Branch("Rayleigh",   &fnRayleigh);
    fEventTree->Branch("Absorption", &fnAbsorb);
    fEventTree->Branch("StepLength", &fStepLength);

    fTrackTree->Branch("InitialX",      &init_x);
    fTrackTree->Branch("InitialY",      &init_y);
    fTrackTree->Branch("InitialZ",      &init_z);
    fTrackTree->Branch("InitialEnergy", &init_energy);
        
    fOutputFile->cd();
    return;
}

// MISC.//

// This function can be used to extract end-of-track data when necessary:

// void TBMC_Analysis::EndOfTrack()
// {
//     return;
// }
