#include "../include/Volunteer.h"
#include "../include/Order.h"
#include <string>
#include <vector>

CollectorVolunteer::CollectorVolunteer(int id, const string &name, int coolDown) : Volunteer(id, name), coolDown(coolDown), timeLeft(NO_ORDER) {}

CollectorVolunteer *CollectorVolunteer::clone() const { return new CollectorVolunteer(*this); }

// not complete
void CollectorVolunteer::step()
{
}

int CollectorVolunteer::getCoolDown() const { return coolDown; }

int CollectorVolunteer::getTimeLeft() const { return timeLeft; }

bool CollectorVolunteer::decreaseCoolDown() // Decrease timeLeft by 1,return true if timeLeft=0,false otherwise
{
    timeLeft--;
    return (timeLeft == 0);
}

// need to go back
bool CollectorVolunteer::hasOrdersLeft() const { return true; }
bool CollectorVolunteer::canTakeOrder(const Order &order) const { return !isBusy(); }

// doesn't work because order is not defined yet
void CollectorVolunteer::acceptOrder(const Order &order) {}
/*
{
    if (canTakeOrder(order))
    {
        activeOrderId = order.getId();
        timeLeft = coolDown;
    }
}
*/

string CollectorVolunteer::toString() const
{
    string s = this->toString() + " ,cool down:" + std::to_string(coolDown) + " ,time left:" + std::to_string(timeLeft);
    return s;
}
