#pragma once
#include "G4VUserActionInitialization.hh"

class MyActionInitialization : public G4VUserActionInitialization {
public:
    MyActionInitialization() = default;
    ~MyActionInitialization() override = default;
    void Build() const override;
};

