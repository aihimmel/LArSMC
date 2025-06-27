#include "TBMC_PrimaryGeneratorAction.hh"
#include "G4Event.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"

#include "G4ParticleGun.hh"
#include "G4GeneralParticleSource.hh"
 #include "G4SingleParticleSource.hh"
  #include "G4SPSAngDistribution.hh"
  #include "G4SPSPosDistribution.hh"
  #include "G4SPSEneDistribution.hh"

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

    ConfigureGPS();
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

void TBMC_PrimaryGeneratorAction::ConfigureGPS()
{
    // General Configuration
    fParticleSource->SetCurrentSourceIntensity(1.);

    // Position Configuration
    auto PosDist = fParticleSource->GetCurrentSource()->GetPosDist();
    PosDist->SetPosDisType("Plane");
    PosDist->SetPosDisShape("Square");
    PosDist->SetCentreCoords(G4ThreeVector(8.75 * cm, 0. * cm, 84.5 * cm));
    PosDist->SetHalfX(0.23 * cm);
    PosDist->SetHalfY(0.23 * cm);

    // Angle Configuration
    auto AngDist = fParticleSource->GetCurrentSource()->GetAngDist();
    AngDist->SetParticleMomentumDirection(G4ThreeVector(0, 0, -1));

    // Energy Configuration
    auto EneDist = fParticleSource->GetCurrentSource()->GetEneDist();
    EneDist->SetEnergyDisType("Mono");
    EneDist->SetMonoEnergy(0.0096 * keV);

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
