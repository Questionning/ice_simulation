#include "MyActionInitialization.hh"
#include "MyPrimaryGeneratorAction.hh"
#include "MySteppingAction.hh"

MyActionInitialization::MyActionInitialization() {}
MyActionInitialization::~MyActionInitialization() {}

void MyActionInitialization::Build() const {
    SetUserAction(new MyPrimaryGeneratorAction());
    SetUserAction(new MySteppingAction());
}
