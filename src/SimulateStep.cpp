#include "../include/Action.h"
#include "../include/WareHouse.h"
#include <string>
#include <vector>

SimulateStep::SimulateStep(int numOfSteps) : numOfSteps(numOfSteps) {}

SimulateStep::SimulateStep(const SimulateStep &other) : numOfSteps(other.numOfSteps) {}

void SimulateStep::act(WareHouse &wareHouse)
{
    for (int i = 0; i < numOfSteps; i++)
        wareHouse.SimulateStepInWarehouse();
    // need to check ifit needs to change to Base Action
    wareHouse.addAction(this);
    this->BaseAction::complete();
}

std::string SimulateStep::toString() const
{
    string s = "SimulateStep " + std::to_string(numOfSteps) + " " + this->BaseAction::statusToString();
    return s;
}

SimulateStep *SimulateStep::clone() const { return new SimulateStep(*this); }
