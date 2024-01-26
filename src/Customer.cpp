#include "../include/Customer.h"
#include <string>
#include <vector>

Customer::Customer(int id, const string &name, int locationDistance, int maxOrders) : id(id), name(name), locationDistance(locationDistance), maxOrders(maxOrders)
{
}

Customer::Customer(const Customer &other) : id(other.id), name(other.name), locationDistance(other.locationDistance), maxOrders(other.maxOrders) {}

const string &Customer::getName() const { return name; }
int Customer::getId() const { return id; }
int Customer::getCustomerDistance() const { return locationDistance; }
int Customer::getMaxOrders() const { return maxOrders; }
int Customer::getNumOrders() const { return ordersId.size(); }
bool Customer::canMakeOrder() const
{
    if (ordersId.size() == maxOrders)
        return false;
    return true;
}
const vector<int> &Customer::getOrdersIds() const { return ordersId; }
int Customer::addOrder(int orderId) // return OrderId if order was added successfully, -1 otherwise
{
    if (this->canMakeOrder())
    {
        ordersId.push_back(orderId);
        return orderId;
    }
    return -1;
}

Customer *Customer::clone() const {} // Return a copy of the customer

Customer::~Customer()
{
}
