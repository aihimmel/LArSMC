#ifndef TBMC_RunAction_h
#define TBMC_RunAction_h 1

#include "globals.hh"
#include "G4UserRunAction.hh"
#include "TBMC_Analysis.hh"

class TBMC_PrimaryGeneratorAction;
class TBMC_Run;

class G4Run;

class TBMC_RunAction : public G4UserRunAction
{
public:
    TBMC_RunAction(TBMC_PrimaryGeneratorAction* = nullptr);
    ~TBMC_RunAction();
    
    G4Run* GenerateRun() override;
    void BeginOfRunAction(const G4Run* run) override;
    void EndOfRunAction(const G4Run* run) override;
    
private:
    TBMC_Run* fRun;
    TBMC_PrimaryGeneratorAction* fPrimary;
    
    TBMC_Analysis*  fAna;
};
#endif
