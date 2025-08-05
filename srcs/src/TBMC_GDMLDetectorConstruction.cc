// Geant4 headers
#include "G4RunManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4VisAttributes.hh"
#include "G4NistManager.hh"
#include "globals.hh"
#include "G4GDMLParser.hh"
// project headers
#include "TBMC_GDMLDetectorConstruction.hh"

TBMC_GDMLDetectorConstruction::TBMC_GDMLDetectorConstruction(G4String fname)
: G4VUserDetectorConstruction() 
{
    fverbose = true;
    gdmlFile = fname;
}

TBMC_GDMLDetectorConstruction::~TBMC_GDMLDetectorConstruction()
{
}

G4VPhysicalVolume *TBMC_GDMLDetectorConstruction::Construct()
{
    ReadGDML();
    G4VPhysicalVolume *worldPhysVol = parser->GetWorldVolume();
    return worldPhysVol;
}

void TBMC_GDMLDetectorConstruction::ConstructSDandField() 
{
}

void TBMC_GDMLDetectorConstruction::ReadGDML()
{
    parser = new G4GDMLParser();
    parser->Read(gdmlFile, false);
    G4VPhysicalVolume *world = parser->GetWorldVolume();

    //----- GDML parser makes world invisible, this is a hack to make it visible again...
    G4LogicalVolume *pworldLogical = world->GetLogicalVolume();
    pworldLogical->SetVisAttributes(0);
    G4cout << world->GetTranslation() << G4endl << G4endl;
    if (fverbose) 

    {
        G4cout << "Found world:  " << world-> GetName() << G4endl;
        G4cout << "world LV:  " << world->GetLogicalVolume()->GetName() << G4endl;
    }
    G4LogicalVolumeStore *pLVStore = G4LogicalVolumeStore::GetInstance();
    if (fverbose)
    {
        G4cout << "Found " << pLVStore->size() << " logical volumes." << G4endl;
    }
    G4PhysicalVolumeStore *pPVStore = G4PhysicalVolumeStore::GetInstance();
    if (fverbose) 
    {
        G4cout << "Found " << pPVStore->size() << " physical volumes." << G4endl;
    }
}
