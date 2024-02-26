#include "TBMC_Run.hh"
#include "G4ParticleDefinition.hh"
#include "G4Run.hh"
#include "G4UnitsTable.hh"

TBMC_Run::TBMC_Run()
: G4Run()
{
    fParticle             = nullptr;
    fRayleighCounter      = 0.;
    fRayleigh2            = 0.;
    fAbsorptionCounter    = 0.;
    fAbsorption2          = 0.;
    fBoundaryCounter      = 0.;
    fBoundary2            = 0.;
}

TBMC_Run::~TBMC_Run() {}

void TBMC_Run::SetPrimary(G4ParticleDefinition* particle)
{
    fParticle = particle;
}

void TBMC_Run::Merge(const G4Run* run)
{
    const TBMC_Run* localRun = static_cast<const TBMC_Run*>(run);
    
    fParticle = localRun->fParticle;
    fRayleighCounter += localRun->fRayleighCounter;
    fRayleigh2 += localRun->fRayleigh2;
    fAbsorptionCounter += localRun->fAbsorptionCounter;
    fAbsorption2 += localRun->fAbsorption2;
    fBoundaryCounter += localRun->fBoundaryCounter;
    fBoundary2 += localRun->fBoundary2;
    
    G4Run::Merge(run);
}

void TBMC_Run::EndOfRun()
{
    if(numberOfEvent == 0)
    {
        return;
    }
    
    G4double TotNbofEvents = G4double(numberOfEvent);
    
    fRayleighCounter /= TotNbofEvents;
    fRayleigh2       /= TotNbofEvents;
    G4double rmsRayleigh = fRayleigh2 - fRayleighCounter * fRayleighCounter;
    if(rmsRayleigh > 0.)
    {
        rmsRayleigh = std::sqrt(rmsRayleigh);
    }
    else
    {
        rmsRayleigh = 0.;
    }
    
    fAbsorptionCounter /= TotNbofEvents;
    fAbsorption2       /= TotNbofEvents;
    G4double rmsAbsorption =
    fAbsorption2 - fAbsorptionCounter * fAbsorptionCounter;
    if(rmsAbsorption > 0.)
    {
        rmsAbsorption = std::sqrt(rmsAbsorption);
    }
    else
    {
        rmsAbsorption = 0.;
    }
        
    fBoundaryCounter /= TotNbofEvents;
    fBoundary2       /= TotNbofEvents;
    G4double rmsBoundary = fBoundary2 - fBoundaryCounter * fBoundaryCounter;
    if(rmsBoundary > 0.)
    {
        rmsBoundary = std::sqrt(rmsBoundary);
    }
    else
    {
        rmsBoundary = 0.;
    }
    
    G4int prec = G4cout.precision(3);
    G4cout << "\n ======================== Run Summary ======================\n";
    G4cout << "Primary particle was: " << fParticle->GetParticleName() << "." << G4endl;
    G4cout << "Number of events: " << numberOfEvent << G4endl;
    G4cout << "Average number of optical Rayleigh interactions per event: "
           << fRayleighCounter << " +- " << rmsRayleigh << G4endl;
    G4cout << "Average number of optical absorption interactions per event: "
           << fAbsorptionCounter << " +- " << rmsAbsorption << G4endl;
    G4cout << "Average number of optical boundary interactions per event: "
           << fBoundaryCounter << " +- " << rmsBoundary << G4endl;
    G4cout.precision(prec);
}
