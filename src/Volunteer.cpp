#include "../include/Volunteer.h"
#include "../include/Order.h"
#include <string>
#include <vector>

Volunteer::Volunteer(int id, const string &name) : id(id), name(name), completedOrderId(NO_ORDER), activeOrderId(NO_ORDER)
{
}

int Volunteer::getId() const { return id; }

const string &Volunteer::getName() const { return name; }

int Volunteer::getActiveOrderId() const { return activeOrderId; }

int Volunteer::getCompletedOrderId() const { return completedOrderId; }

bool Volunteer::isBusy() const
{
    if (activeOrderId != -1)
        return true;
    return false;
}

bool Volunteer::hasOrdersLeft() const {}                  // Signal whether the volunteer didn't reach orders limit,Always true for CollectorVolunteer and DriverVolunteer
bool Volunteer::canTakeOrder(const Order &order) const {} // Signal if the volunteer can take the order.
void Volunteer::acceptOrder(const Order &order) {}        // Prepare for new order(Reset activeOrderId,TimeLeft,DistanceLeft,OrdersLeft depends on the volunteer type)

void Volunteer::step() {} // Simulate volunteer step,if the volunteer finished the order, transfer activeOrderId to completedOrderId

string Volunteer::toString() const
{
    return std::to_string(id) + " " + name;
}
Volunteer *Volunteer::clone() const {} // Return a copy of the volunteer
