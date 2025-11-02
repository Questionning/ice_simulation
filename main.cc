#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "G4PhysListFactory.hh"
#include "G4VModularPhysicsList.hh"

#include "MyDetectorConstruction.hh"
#include "MyPrimaryGeneratorAction.hh"
#include "MyActionInitialization.hh"

#include "Randomize.hh"

#include <ctime>
#include <iostream>

int main(int argc, char** argv)
{
    // Random seed
    CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
    CLHEP::HepRandom::setTheSeed(time(NULL));

    // Create Run Manager
    auto* runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Serial);

    // User Initialization classes
    runManager->SetUserInitialization(new MyDetectorConstruction());

    // Use built-in physics list
    G4PhysListFactory factory;
    G4VModularPhysicsList* phys = factory.GetReferencePhysList("FTFP_BERT");
    runManager->SetUserInitialization(phys);

    // User Action Initialization
    runManager->SetUserInitialization(new MyActionInitialization());

    // Initialize
    runManager->Initialize();

    // Run a few events to test
    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    UImanager->ApplyCommand("/run/beamOn 10");

    delete runManager;
    return 0;
}
