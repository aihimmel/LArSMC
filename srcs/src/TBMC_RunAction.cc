#include "TBMC_RunAction.hh"
#include "TBMC_PrimaryGeneratorAction.hh"
#include "TBMC_Run.hh"
#include "G4ParticleDefinition.hh"
#include "G4Run.hh"

TBMC_RunAction::TBMC_RunAction(TBMC_PrimaryGeneratorAction* prim)
: G4UserRunAction()
, fRun(nullptr)
, fPrimary(prim)
, fAna(nullptr)
{}

TBMC_RunAction::~TBMC_RunAction()
{
    if(fAna) delete fAna;
}

G4Run* TBMC_RunAction::GenerateRun()
{
    fRun = new TBMC_Run();
    return fRun;
}

void TBMC_RunAction::BeginOfRunAction(const G4Run* run)
{
    G4cout<<"Starting run: "<<run->GetRunID()<<G4endl;
    
    if(fPrimary)
    {
        G4ParticleDefinition* particle = fPrimary->GetParticleSource()->GetParticleDefinition();
        fRun->SetPrimary(particle);
    }

    fAna = TBMC_Analysis::getInstance();
    fAna->BeginOfRun();

    return;
}

void TBMC_RunAction::EndOfRunAction(const G4Run* run)
{
    fAna->EndOfRun();
    G4cout<<"Completed processing run: "<<run->GetRunID()<<G4endl;
    G4cout<<"Output stored in: "<< TBMC_Analysis::fFilename <<G4endl;
    
    if(isMaster) fRun->EndOfRun();
}
