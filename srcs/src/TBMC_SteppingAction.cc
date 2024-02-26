#include "TBMC_SteppingAction.hh"
#include "TBMC_Run.hh"
#include "G4Event.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4OpticalPhoton.hh"
#include "G4RunManager.hh"
#include "G4Step.hh"
#include "G4Track.hh"

TBMC_SteppingAction::TBMC_SteppingAction(TBMC_EventAction* event)
: G4UserSteppingAction()
, fEventAction(event)
{   
    fAna = TBMC_Analysis::getInstance();
}

TBMC_SteppingAction::~TBMC_SteppingAction() {}

void TBMC_SteppingAction::UserSteppingAction(const G4Step* step)
{
    opPhoton_DoIt(step);
}

void TBMC_SteppingAction::scattProc_DoIt(const G4Step* step)
{
    if(!isProcess("OpRayleigh", step))
    {
        return;
    }

    fAna->fnRayleigh++;
    
    fEventAction->AddRayleigh();
    return;
}

void TBMC_SteppingAction::absProc_DoIt(const G4Step* step)
{
    if(!isProcess("OpAbsorption", step))
    {
        return;
    }

    fAna->fnAbsorb++;
    
    fEventAction->AddAbsorption();
    return;
}

void TBMC_SteppingAction::boundaryProc_DoIt(const G4Step* step)
{
    // for boundary scattering, process name in 'transportation'. Need to check differently:
    G4StepPoint* endPoint = step->GetPostStepPoint();
    static G4ParticleDefinition* opticalphoton =  G4OpticalPhoton::OpticalPhotonDefinition();
    if(endPoint->GetStepStatus() == fGeomBoundary)
    {
        G4OpBoundaryProcessStatus theStatus = Undefined;
        G4ProcessManager* opManager         = opticalphoton->GetProcessManager();
        G4int n_proc                        = opManager->GetPostStepProcessVector(typeDoIt)->entries();
        G4ProcessVector* postStepDoItVector = opManager->GetPostStepProcessVector(typeDoIt);
        for(G4int i = 0; i < n_proc; ++i)
        {
            G4VProcess* currentProcess  = (*postStepDoItVector)[i];
            G4OpBoundaryProcess* opProc = dynamic_cast<G4OpBoundaryProcess*>(currentProcess);
            if(opProc)  theStatus = opProc->GetStatus();
        }
        if(theStatus != Undefined && theStatus != NotAtBoundary &&  theStatus != StepTooSmall)
        {
            fEventAction->AddBoundary();
        }
    }
    return;
}

void TBMC_SteppingAction::opPhoton_DoIt(const G4Step* step)
{
    if(!isParticle("opticalphoton", step))
    {
        return;
    }
    
    absProc_DoIt(step);
    scattProc_DoIt(step);
    boundaryProc_DoIt(step);
    
    G4String proName;
    if(step->GetPreStepPoint()->GetProcessDefinedStep())
    {
        proName = step->GetPreStepPoint()->GetProcessDefinedStep()->GetProcessName(); //The process before detection
    }
    else
    {
        proName = "InitialTransportation";
    }
    fAna->fProcessName = (std::string)proName;
    G4String volName = step->GetTrack()->GetVolume()->GetName();
    G4double stepLen = step->GetStepLength();
    
//    stepVerboseInfo(step);
    
    if(isVolume("volTank", step) || isVolume("volCage",step))
    {
        fAna->fKillVolName = (std::string)volName;
        fAna->fStepLength  = stepLen;
        fAna->fopDetID     = 9; //It is not detected by any optial detector

        step->GetTrack()->SetTrackStatus(fKillTrackAndSecondaries);
        return;
    }
    
    if(isVolume("volOpDet", step))
    {
        int nPos_1 = volName.find("_");
        int nPos_2 = volName.find_last_of("_");
        G4String opDetIDstr = volName(nPos_1+1, nPos_2-nPos_1-1);
        int    opDetID      = atoi(opDetIDstr.data());
        
        fAna->fKillVolName = (std::string)volName;
        fAna->fStepLength  = stepLen;
        fAna->fopDetID     = opDetID;
        
        step->GetTrack()->SetTrackStatus(fKillTrackAndSecondaries);
        return;
    }
    
    return;
}

G4int TBMC_SteppingAction::isParticle(const char* particleName,const G4Step* step)
{
    if(step->GetTrack()->GetParticleDefinition()->GetParticleName().contains(particleName))
    {
        return 1;
    }
    
    return 0;
}

G4int TBMC_SteppingAction::isProcess(const char* processName,const G4Step* step)
{
    if(step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName().contains(processName))
    {
        return 1;
    }
    return 0;
}

G4int TBMC_SteppingAction::isVolume(const char* volumeName,const G4Step* step)
{
    if(!step->GetTrack()->GetVolume())
    {
        return 0;
    }
    if(!step->GetTrack()->GetVolume()->GetName().contains(volumeName))
    {
        return 0;
    }
    
    return 1;
}

G4int TBMC_SteppingAction::isNextVolume(const char* nextVolumeName,const G4Step* step)
{
    if(!step->GetTrack()->GetNextVolume())
    {
        return 0;
    }
    if(!step->GetTrack()->GetNextVolume()->GetName().contains(nextVolumeName))
    {
        return 0;
    }
    
    return 1;
}
void TBMC_SteppingAction::stepVerboseInfo(const G4Step* step)
{
    G4cout<<"SteppingAction(..): "
      <<step->GetTrack()->GetTrackStatus() <<"\t "
      <<step->GetTrack()->GetParticleDefinition()->GetParticleName() <<"\t "
      <<step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() <<"\t steplength [cm] "
      <<step->GetStepLength() <<"\t current vol: "
      <<step->GetTrack()->GetVolume()->GetName() <<"\t current pos: "
      <<step->GetDeltaPosition();

    if(step->GetTrack()->GetNextVolume())
    {
        G4cout<<"\t next vol: "<<step->GetTrack()->GetNextVolume()->GetName();
    }

    G4cout << G4endl;
    return;
}
