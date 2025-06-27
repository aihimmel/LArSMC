#ifndef TBMC_TrackingAction_h
#define TBMC_TrackingAction_h

#include "globals.hh"
#include "G4UserTrackingAction.hh"
#include "TBMC_Analysis.hh"

class G4Track;
class G4TrackingManager;

class TBMC_TrackingAction : public G4UserTrackingAction
{
public:
    TBMC_TrackingAction();
    ~TBMC_TrackingAction() override;

    void PreUserTrackingAction (const G4Track*) override;
    // void PostUserTrackingAction (const G4Track*) override;   // Not presently needed.

private:
    TBMC_Analysis* fAna;
};

#endif
