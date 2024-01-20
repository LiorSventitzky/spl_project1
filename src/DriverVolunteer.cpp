#include "../include/Volunteer.h"
#include "../include/Order.h"
#include <string>
#include <vector>

DriverVolunteer::DriverVolunteer(int id, const string &name, int maxDistance, int distancePerStep) : maxDistance(maxDistance), distancePerStep(distancePerStep), distanceLeft(NO_ORDER), Volunteer(id, name) {}

DriverVolunteer *DriverVolunteer::clone() const { return new DriverVolunteer(*this); }

int DriverVolunteer::getDistanceLeft() const { return distanceLeft; }
int DriverVolunteer::getMaxDistance() const { return maxDistance; }
int DriverVolunteer::getDistancePerStep() const { return distancePerStep; }

bool DriverVolunteer::decreaseDistanceLeft() // Decrease distanceLeft by distancePerStep,return true if distanceLeft<=0,false otherwise
{
    distanceLeft = distanceLeft - distancePerStep;
    return distanceLeft <= 0;
}

bool DriverVolunteer::hasOrdersLeft() const { return true; }

// doesn't work because order is not defined yet
bool DriverVolunteer::canTakeOrder(const Order &order) const {} // Signal if the volunteer is not busy and the order is within the maxDistance
/*
{
    return !isBusy() && maxDistance >= order.getDistance();
}
*/

// doesn't work because order is not defined yet
void DriverVolunteer::acceptOrder(const Order &order) {} // Assign distanceLeft to orders distance
/*
{
    if (canTakeOrder(order))
    {
        distanceLeft = order.getDistance();
        activeOrderId = order.getId();
    }
}
*/

// not complete
void DriverVolunteer::step() {} // Decrease distanceLeft by distancePerStep

string DriverVolunteer::toString() const
{
    string s = this->toString() + " max distance:" + std::to_string(maxDistance) + " distance per step:" + std::to_string(distancePerStep) + " distance left:" + std::to_string(distanceLeft);
    return s;
}
