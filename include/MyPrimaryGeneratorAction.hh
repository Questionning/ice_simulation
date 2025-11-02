
#pragma once
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"

class MyPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
    MyPrimaryGeneratorAction();
    ~MyPrimaryGeneratorAction() override;
    void GeneratePrimaries(G4Event* anEvent) override;

private:
    G4ParticleGun* fParticleGun;
};
