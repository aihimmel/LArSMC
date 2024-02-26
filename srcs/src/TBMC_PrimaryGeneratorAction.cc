#include "TBMC_PrimaryGeneratorAction.hh"
#include "G4Event.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

TBMC_PrimaryGeneratorAction::TBMC_PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction()
, fParticleSource(nullptr)
{
    fParticleSource  = new G4GeneralParticleSource;
    
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();  
    G4ParticleDefinition* particle = particleTable->FindParticle("opticalphoton");
    
    fParticleSource->SetParticleDefinition(particle);
}

TBMC_PrimaryGeneratorAction::~TBMC_PrimaryGeneratorAction()
{
    if(!fParticleSource) delete fParticleSource;
}

void TBMC_PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    if(fParticleSource->GetParticleDefinition()->GetParticleName() == "opticalphoton")
    {
        fParticleSource->SetParticlePolarization(getRandomPolarization(fParticleSource->GetParticleMomentumDirection()));
    }
    
    fParticleSource->GeneratePrimaryVertex(anEvent);
    
    return;
}

G4ThreeVector TBMC_PrimaryGeneratorAction::getRandomPolarization(G4ThreeVector particleMomentumDirection)
{
    if(fParticleSource->GetParticleDefinition()->GetParticleName() != "opticalphoton")
    {
         return G4ThreeVector(1.,0.,0.);
    }

    if(!particleMomentumDirection.mag())
    {
        G4cout<<"photon momentum = 0. return default value (1.,0.,0.) for photon polarization."<<G4endl;
        return G4ThreeVector(1.,0.,0.);
    }

    G4ThreeVector e1,e2;
    e1 = particleMomentumDirection.orthogonal(); e1 = e1/e1.mag();
    e2 = e1.cross(particleMomentumDirection);    e2 = e2/e2.mag();
    
    G4double phi = G4UniformRand()*360.*deg;
    
    G4ThreeVector polar = e1*cos(phi) + e2*sin(phi);
    return polar;
}
