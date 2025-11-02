#include "MySteppingAction.hh"
#include "G4Step.hh"
#include "G4EventManager.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include <fstream>

std::ofstream outfile;

MySteppingAction::MySteppingAction() {
    G4cout << "Opening muon_data.csv..." << G4endl;
    outfile.open("muon_data.csv");
    if (!outfile.is_open()) {
        G4cout << "Failed to open file!" << G4endl;
        G4Exception("MySteppingAction::MySteppingAction()", "OpenError",
                   FatalException, "Cannot open muon_data.csv");
    }
    G4cout << "File opened successfully" << G4endl;
    outfile << "Event,Track,Material,StepLength(mm),Edep(MeV),PreE(MeV),PostE(MeV),"
            << "PreZ(mm),PostZ(mm),Transmission\n";
    outfile.flush();
}

MySteppingAction::~MySteppingAction() {
    G4cout << "Closing file..." << G4endl;
    if (outfile.is_open()) {
        outfile.flush();
        outfile.close();
    }
}

void MySteppingAction::UserSteppingAction(const G4Step* step)
{
    if (!outfile.is_open()) {
        G4cout << "File not open during stepping action!" << G4endl;
        return;
    }

    auto prePoint = step->GetPreStepPoint();
    auto postPoint = step->GetPostStepPoint();
    auto track = step->GetTrack();
    auto eventID = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();

    G4String material = "";
    if (prePoint->GetMaterial()) material = prePoint->GetMaterial()->GetName();

    auto preE  = prePoint->GetKineticEnergy()/MeV;
    auto postE = postPoint->GetKineticEnergy()/MeV;
    auto stepL = step->GetStepLength()/mm;
    auto edep  = step->GetTotalEnergyDeposit()/MeV;
    auto preZ  = prePoint->GetPosition().z()/mm;
    auto postZ = postPoint->GetPosition().z()/mm;

    // Transmission flag (1 if still alive after block)
    G4bool transmitted = (track->GetTrackStatus() == fAlive);

    outfile << eventID << "," << track->GetTrackID() << "," << material << ","
            << stepL << "," << edep << "," << preE << "," << postE << ","
            << preZ << "," << postZ << "," << transmitted << "\n";
}
