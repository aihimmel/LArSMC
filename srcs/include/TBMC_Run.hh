#ifndef TBMC_Run_h
#define TBMC_Run_h 1

#include "G4Run.hh"

class G4ParticleDefinition;

class TBMC_Run : public G4Run
{
public:
    TBMC_Run();
    ~TBMC_Run();
    
    void SetPrimary(G4ParticleDefinition* particle);
    
    void AddRayleigh(G4double n)
    {
         fRayleighCounter += n;
         fRayleigh2 += n * n;
    };
    void AddAbsorption(G4double n)
    {
        fAbsorptionCounter += n;
        fAbsorption2 += n * n;
    };
    void AddBoundary(G4double n)
    {
        fBoundaryCounter += n;
        fBoundary2 += n * n;
    };
    
    void Merge(const G4Run*) override;
    void EndOfRun();

private:
    G4double fRayleighCounter;
    G4double fRayleigh2;
    G4double fAbsorptionCounter;
    G4double fAbsorption2;
    G4double fBoundaryCounter;
    G4double fBoundary2;
    
    G4ParticleDefinition* fParticle;
};
#endif
