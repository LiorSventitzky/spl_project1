#include "../include/Customer.h"
#include "../include/Volunteer.h"
#include "../include/Order.h"
#include <string>
#include <vector>

Order::Order(int id, int customerId, int distance) : id(id), customerId(customerId), distance(distance), status(OrderStatus::PENDING), collectorId(NO_VOLUNTEER), driverId(NO_VOLUNTEER) {}
Order::Order(Order &other) : id(other.id), customerId(other.customerId), distance(other.distance), status(other.status), collectorId(other.collectorId), driverId(other.driverId) {}
int Order::getId() const { return id; }
int Order::getCustomerId() const { return customerId; }
int Order::getDistance() const { return distance; }
void Order::setStatus(OrderStatus status) { this->status = status; }
void Order::setCollectorId(int collectorId) { this->collectorId = collectorId; }
void Order::setDriverId(int driverId) { this->driverId = driverId; }
int Order::getCollectorId() const { return collectorId; }
int Order::getDriverId() const { return driverId; }
OrderStatus Order::getStatus() const { return status; }
const string Order::toString() const
{
    string stat;
    if (status == OrderStatus::PENDING)
        stat = "PENDING";
    else if (status == OrderStatus::COLLECTING)
        stat = "COLLECTING";
    else if (status == OrderStatus::DELIVERING)
        stat = "DELIVERING";
    else if (status == OrderStatus::COMPLETED)
        stat = "COMPLETED";
    else
        stat = "UNKNOWN";

    string s = " OrderId:" + std::to_string(id) + " OrderStatus:" + stat + " customerId:" + std::to_string(customerId) + " distance:" + std::to_string(distance)  +" collectorId:" + std::to_string(collectorId) + " driverId:" + std::to_string(driverId);
    return s;
}
const string Order::shortenedToString() const
{
    string stat;
    if (status == OrderStatus::PENDING)
        stat = "PENDING";
    else if (status == OrderStatus::COLLECTING)
        stat = "COLLECTING";
    else if (status == OrderStatus::DELIVERING)
        stat = "DELIVERING";
    else if (status == OrderStatus::COMPLETED)
        stat = "COMPLETED";
    else
        stat = "UNKNOWN";
    return "OrderId: " + std::to_string(id) + "\nOrderStatus: " + stat + "\n";
}

Order *Order::clone()
{
    return new Order(*this);
}
