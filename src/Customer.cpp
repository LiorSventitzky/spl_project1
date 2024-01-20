#include "../include/Customer.h"
#include <string>
#include <vector>

Customer::Customer(int id, const string &name, int locationDistance, int maxOrders) : id(id), name(name), locationDistance(locationDistance), maxOrders(maxOrders)
{
}

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
int Customer::addOrder(int orderId)
// עוד לא ממ
{ // return OrderId if order was added successfully, -1 otherwise
    ordersId.push_back(orderId);
    return orderId;
}
Customer *Customer::clone() const {} // Return a copy of the customer
;
