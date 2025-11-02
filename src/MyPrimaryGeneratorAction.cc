#include "MyPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

MyPrimaryGeneratorAction::MyPrimaryGeneratorAction()
{
    fParticleGun = new G4ParticleGun(1);
}

MyPrimaryGeneratorAction::~MyPrimaryGeneratorAction()
{
    delete fParticleGun;
}

void MyPrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
    auto particleTable = G4ParticleTable::GetParticleTable();
    auto muon = particleTable->FindParticle("mu-");

    fParticleGun->SetParticleDefinition(muon);

    // --- Atmospheric muon spectrum (simplified) ---
    // Typical energy range 1–100 GeV, approximate E^-2.7 spectrum
    G4double E_min = 1.*GeV;
    G4double E_max = 100.*GeV;
    G4double r = G4UniformRand();
    G4double energy = std::pow(std::pow(E_min, -1.7) - r * (std::pow(E_min, -1.7) - std::pow(E_max, -1.7)), -1/1.7);
    fParticleGun->SetParticleEnergy(energy);

    // Direction: mostly downward with small angular spread
    G4double theta = std::acos(1 - 2*G4UniformRand()); // isotropic for now
    G4double phi   = 2*M_PI*G4UniformRand();
    G4ThreeVector dir(std::sin(theta)*std::cos(phi),
                      std::sin(theta)*std::sin(phi),
                      -std::abs(std::cos(theta))); // downward

    fParticleGun->SetParticleMomentumDirection(dir);

    // Start 1 m above the block
    fParticleGun->SetParticlePosition(G4ThreeVector(0, 0, 1.5*m));

    fParticleGun->GeneratePrimaryVertex(event);
}
