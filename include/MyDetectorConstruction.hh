#pragma once
#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction {
public:
    MyDetectorConstruction() = default;
    ~MyDetectorConstruction() override = default;
    G4VPhysicalVolume* Construct() override;
};

