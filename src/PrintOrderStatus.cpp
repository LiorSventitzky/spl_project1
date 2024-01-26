#include <string>
#include <vector>
#include "../include/Action.h"
#include "../include/WareHouse.h"

PrintOrderStatus::PrintOrderStatus(int id) : orderId(id) {}

PrintOrderStatus::PrintOrderStatus(const PrintOrderStatus &other) : orderId(other.orderId) {}

void PrintOrderStatus::act(WareHouse &wareHouse)
{
    int orderCounter = wareHouse.getOrderCounter();
    if (orderId <= orderCounter)
    {
        wareHouse.printOrderStatus(orderId);
        this->BaseAction::complete();
    }
    else
        this->BaseAction::error("Order was not found");
    wareHouse.addAction(this);
};

PrintOrderStatus *PrintOrderStatus::clone() const { return new PrintOrderStatus(*this); };

string PrintOrderStatus::toString() const
{
    string s = "print order status " + std::to_string(orderId) + " " + this->BaseAction::statusToString();
    return s;
}
