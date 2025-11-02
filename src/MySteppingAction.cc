#include "MySteppingAction.hh"
#include "G4Step.hh"
#include "G4EventManager.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include <fstream>

static std::ofstream outfile("muon_data.csv");

MySteppingAction::MySteppingAction() {
    outfile << "Event,Track,Material,StepLength(mm),Edep(MeV),PreE(MeV),PostE(MeV),"
               "PreZ(mm),PostZ(mm),Transmission\n";
}

MySteppingAction::~MySteppingAction() {
    outfile.close();
}

void MySteppingAction::UserSteppingAction(const G4Step* step)
{
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
