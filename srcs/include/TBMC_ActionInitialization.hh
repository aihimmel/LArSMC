#ifndef TBMC_ActionInitialization_h
#define TBMC_ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class TBMC_ActionInitialization : public G4VUserActionInitialization
{
public:
    TBMC_ActionInitialization();
    ~TBMC_ActionInitialization();
    
    void BuildForMaster() const override;
    void Build() const override;
};

#endif