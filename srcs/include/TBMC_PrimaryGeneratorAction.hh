#ifndef TBMC_PrimaryGeneratorAction_h
#define TBMC_PrimaryGeneratorAction_h 1

#include "globals.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4GeneralParticleSource.hh"

class G4Event;
class TBMC_PrimaryGeneratorMessenger;

class TBMC_PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
    TBMC_PrimaryGeneratorAction();
    ~TBMC_PrimaryGeneratorAction();
    
    void GeneratePrimaries(G4Event*) override;
    G4ThreeVector getRandomPolarization(G4ThreeVector particleMomentumDirection);
        
    G4GeneralParticleSource* GetParticleSource() { return fParticleSource; }

private:
    G4GeneralParticleSource* fParticleSource;
};
#endif
