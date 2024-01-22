#include "../include/Volunteer.h"
#include "../include/Order.h"
#include <string>
#include <vector>

DriverVolunteer::DriverVolunteer(int id, const string &name, int maxDistance, int distancePerStep) : Volunteer(id, name), maxDistance(maxDistance), distancePerStep(distancePerStep), distanceLeft(NO_ORDER) {}

DriverVolunteer::DriverVolunteer(const DriverVolunteer &other) : Volunteer(other), maxDistance(other.maxDistance), distancePerStep(other.distancePerStep), distanceLeft(other.distanceLeft) {}

DriverVolunteer *DriverVolunteer::clone() const
{
    return new DriverVolunteer(*this);
}

int DriverVolunteer::getDistanceLeft() const { return distanceLeft; }
int DriverVolunteer::getMaxDistance() const { return maxDistance; }
int DriverVolunteer::getDistancePerStep() const { return distancePerStep; }

bool DriverVolunteer::decreaseDistanceLeft() // Decrease distanceLeft by distancePerStep,return true if distanceLeft<=0,false otherwise
{
    distanceLeft = distanceLeft - distancePerStep;
    return distanceLeft <= 0;
}

bool DriverVolunteer::hasOrdersLeft() const { return true; }

bool DriverVolunteer::canTakeOrder(const Order &order) const // Signal if the volunteer is not busy and the order is within the maxDistance
{
    return !isBusy() && maxDistance >= order.getDistance();
}

void DriverVolunteer::acceptOrder(const Order &order) // Assign distanceLeft to orders distance
{
    if (canTakeOrder(order))
    {
        distanceLeft = order.getDistance();
        activeOrderId = order.getId();
    }
}

void DriverVolunteer::step()
{ // Decrease distanceLeft by distancePerStep
    if (decreaseDistanceLeft())
    {
        distanceLeft = NO_ORDER;
        completedOrderId = activeOrderId;
        activeOrderId = NO_ORDER;
    }
}

string DriverVolunteer::toString() const
{
    string s = Volunteer::toString() + " max distance:" + std::to_string(maxDistance) + " distance per step:" + std::to_string(distancePerStep) + " distance left:" + std::to_string(distanceLeft) + " ,type: Driver";
    return s;
}
