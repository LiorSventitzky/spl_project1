#include "../include/Action.h"
#include "../include/WareHouse.h"

BackupWareHouse::BackupWareHouse() {}
void BackupWareHouse::act(WareHouse &wareHouse)
{
    wareHouse.createBackUp();
    BaseAction::complete();
    wareHouse.addAction(this);
}
BackupWareHouse *BackupWareHouse::clone() const
{
    return new BackupWareHouse(*this);
}
string BackupWareHouse::toString() const
{
    string s = "BackupWarehouse: " + this->BaseAction::statusToString();
    return s;
}
