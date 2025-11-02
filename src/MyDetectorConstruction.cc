#include "MyDetectorConstruction.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

MyDetectorConstruction::MyDetectorConstruction() {}
MyDetectorConstruction::~MyDetectorConstruction() {}

G4VPhysicalVolume* MyDetectorConstruction::Construct()
{
    G4NistManager* nist = G4NistManager::Instance();

    // World volume
    G4double world_size = 5.0*m;
    G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");

    auto solidWorld = new G4Box("World", world_size/2, world_size/2, world_size/2);
    auto logicWorld = new G4LogicalVolume(solidWorld, world_mat, "World");
    auto physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0);

    // Iron block (1x1x1 m³)
    G4Material* iron = nist->FindOrBuildMaterial("G4_Fe");
    G4double block_size = 1.0*m;
    auto solidBlock = new G4Box("IronBlock", block_size/2, block_size/2, block_size/2);
    auto logicBlock = new G4LogicalVolume(solidBlock, iron, "IronBlock");
    new G4PVPlacement(0, G4ThreeVector(0,0,0), logicBlock, "IronBlock", logicWorld, false, 0);

    return physWorld;
}
