#include "../include/Volunteer.h"
#include "../include/Order.h"
#include <string>
#include <vector>

LimitedDriverVolunteer::LimitedDriverVolunteer(int id, const string &name, int maxDistance, int distancePerStep, int maxOrders) : DriverVolunteer(id, name, maxDistance, distancePerStep), maxOrders(maxOrders), ordersLeft(maxOrders){};

LimitedDriverVolunteer *LimitedDriverVolunteer::clone() const { return new LimitedDriverVolunteer(*this); }
int LimitedDriverVolunteer::getMaxOrders() const { return maxOrders; }
int LimitedDriverVolunteer::getNumOrdersLeft() const { return ordersLeft; }
bool LimitedDriverVolunteer::hasOrdersLeft() const { return (ordersLeft > 0); }
bool LimitedDriverVolunteer::canTakeOrder(const Order &order) const
{
    return this->canTakeOrder(order) && (ordersLeft > 0);
}

void LimitedDriverVolunteer::acceptOrder(const Order &order)
{ // Assign distanceLeft to order's distance and decrease ordersLeft
    this->acceptOrder(order);
    ordersLeft--;
}
string LimitedDriverVolunteer::toString() const
{
    string s = this->toString() + " max orders:" + std::to_string(ordersLeft) + " orders left:" + std::to_string(ordersLeft);
    return s;
}
