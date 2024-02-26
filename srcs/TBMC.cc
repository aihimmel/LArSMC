#include "TBMC_GDMLDetectorConstruction.hh"
#include "TBMC_ActionInitialization.hh"
#include "TBMC_Analysis.hh"

#include "FTFP_BERT.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4OpticalPhysics.hh"
#include "G4RunManager.hh"

//#include "G4Types.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4UIsession.hh"
#include "G4UIterminal.hh"
#include "TStopwatch.h"

namespace {

    void PrintUsage() {
        G4cerr << " Usage: " << G4endl;
        G4cerr << " TBMC_ [-g gdmlfile] [-m macro ] [-o outfile][-r seed] " << G4endl;
    }
}
int main(int argc, char** argv)
{
    TStopwatch timer;
    timer.Start();

    if (argc > 7)
    {
        PrintUsage();
        return 1;
    }
    
    G4String gdmlfile = "";
    G4String macro;
    G4String outfile = "test.root";
    G4long   seed = 345354;
    
    for (G4int i = 1; i < argc; i = i + 2)
    {
        if (G4String(argv[i]) == "-g") gdmlfile = argv[i + 1];
        else if (G4String(argv[i]) == "-m") macro = argv[i + 1];
        else if (G4String(argv[i]) == "-o") outfile = argv[i + 1];
        else if (G4String(argv[i]) == "-r") seed = atoi(argv[i + 1]);
        else 
        {
            PrintUsage();
            return 1;
        }
    }
    
    G4Random::setTheSeed(seed);
    TBMC_Analysis::fFilename = outfile;
    
    G4RunManager* runManager = new G4RunManager;
    if (gdmlfile == "")
    {
        G4cout << "No gdml file specified" << G4endl;
        return 1;
    }
    runManager->SetUserInitialization(new TBMC_GDMLDetectorConstruction(gdmlfile));
    
    G4VModularPhysicsList* physicsList = new FTFP_BERT;
    physicsList->ReplacePhysics(new G4EmStandardPhysics_option4());
    G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();
    physicsList->RegisterPhysics(opticalPhysics);
    runManager->SetUserInitialization(physicsList);
    runManager->SetUserInitialization(new TBMC_ActionInitialization());

    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();
    //G4UImanager* UImanager = G4UImanager::GetUIpointer();
    
    if (macro.size())
    {
        G4UImanager* UImanager = G4UImanager::GetUIpointer();
        G4String command = "/control/execute ";
        UImanager->ApplyCommand(command + macro);
    }
    else
    {
        G4UIsession* session = new G4UIterminal();
        session->SessionStart();
        delete session;
    }

    delete visManager;
    delete runManager;
    
    timer.Stop();
    cout<<"Running completes: CPU time "<<timer.CpuTime()<<"\t Real time "<<timer.RealTime()<<endl;
  
    return 0;
}
