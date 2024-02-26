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
    
    fAnaTree    = NULL;
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
    fAnaTree->Write();
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
    fAnaTree->Fill();
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
    G4cout<<"Creating tree  "<<fFilename<<G4endl;
    fOutputFile = new TFile(fFilename, "RECREATE");
    fAnaTree    = new TTree("TBMC", "TBMC");

    fAnaTree->Branch("KillVol",    &fKillVolName);
    fAnaTree->Branch("Process",    &fProcessName);
    fAnaTree->Branch("OpDet",      &fopDetID);
    fAnaTree->Branch("Rayleigh",   &fnRayleigh);
    fAnaTree->Branch("Absorption", &fnAbsorb);
    fAnaTree->Branch("StepLength", &fStepLength);
        
    fOutputFile->cd();
    return;
}
