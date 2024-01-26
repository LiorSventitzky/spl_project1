#include "../include/Action.h"
#include "../include/WareHouse.h"

RestoreWareHouse::RestoreWareHouse()
{
}

void RestoreWareHouse::act(WareHouse &wareHouse)
{
    wareHouse.restoreWarehouse();
    BaseAction::complete();
    wareHouse.addAction(this);
}

RestoreWareHouse *RestoreWareHouse::clone() const
{
    return new RestoreWareHouse(*this);
}

string RestoreWareHouse::toString() const
{
    string s = "RestorWareHouse: " + this->BaseAction::statusToString();
    return s;
}