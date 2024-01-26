#include "../include/Volunteer.h"
#include "../include/Order.h"
#include <string>
#include <vector>

Volunteer::Volunteer(int id, const string &name) : id(id), name(name), completedOrderId(NO_ORDER), activeOrderId(NO_ORDER)
{
}

Volunteer::Volunteer(const Volunteer &other) : id(other.id), name(other.name), completedOrderId(NO_ORDER), activeOrderId(NO_ORDER) {}

int Volunteer::getId() const
{
    return id;
}

const string &Volunteer::getName() const { return name; }

int Volunteer::getActiveOrderId() const { return activeOrderId; }

int Volunteer::getCompletedOrderId() const { return completedOrderId; }

void Volunteer::finishCompletedOrder() { completedOrderId = NO_ORDER; }

bool Volunteer::isBusy() const
{
    if (activeOrderId != -1)
        return true;
    return false;
}

bool Volunteer::hasOrdersLeft() const
{ // Signal whether the volunteer didn't reach orders limit,Always true for CollectorVolunteer and DriverVolunteer
}
void Volunteer::step() {} // Simulate volunteer step,if the volunteer finished the order, transfer activeOrderId to completedOrderId

string Volunteer::toString() const
{
    return "id:" + std::to_string(id) + "  name:" + name + " activeOrderID:" + std::to_string(activeOrderId) + " completeOrderID:" + std::to_string(completedOrderId);
}

Volunteer::~Volunteer() {}
