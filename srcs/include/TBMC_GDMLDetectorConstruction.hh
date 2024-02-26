#ifndef TBMC_GDMLDetectorConstruction_h
#define TBMC_GDMLDetectorConstruction_h 1
#include "G4VUserDetectorConstruction.hh"
class G4GDMLParser;

class TBMC_GDMLDetectorConstruction : public G4VUserDetectorConstruction 
{
public:
    TBMC_GDMLDetectorConstruction(G4String fname);
    virtual ~TBMC_GDMLDetectorConstruction();
    void ReadGDML();
    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

private:
    TBMC_GDMLDetectorConstruction & operator=(const TBMC_GDMLDetectorConstruction &right);
    TBMC_GDMLDetectorConstruction(const TBMC_GDMLDetectorConstruction&);
    G4GDMLParser *parser;
    G4String gdmlFile;
    G4bool fverbose;
};
#endif
