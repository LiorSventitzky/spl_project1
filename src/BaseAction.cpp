#include "../include/Action.h"
#include "../include/WareHouse.h"
#include "../include/Customer.h"
#include "../include/Volunteer.h"
#include "../include/Order.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

BaseAction::BaseAction() { errorMsg = "there is an error!!!"; }
ActionStatus BaseAction::getStatus() const { return status; }
virtual void BaseAction::act(WareHouse &wareHouse) = 0;
virtual string BaseAction::toString() const = 0;
virtual BaseAction *BaseAction::clone() const = 0;

void BaseAction::complete() { status = ActionStatus::COMPLETED }
void BaseAction::error(string errorMsg)
{
    status = ActionStatus::COMPLETED;
    std::cout << "Error: " + errorMsg << std::endl;
}
string BaseAction::getErrorMsg() const { return errorMsg; }
