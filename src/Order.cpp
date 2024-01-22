#include "../include/Customer.h"
#include "../include/Volunteer.h"
#include "../include/Order.h"
#include <string>
#include <vector>

Order::Order(int id, int customerId, int distance) : id(id), customerId(customerId), distance(distance), status(OrderStatus::PENDING), collectorId(NO_VOLUNTEER), driverId(NO_VOLUNTEER) {}
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

    string s = "id:" + std::to_string(id) + " customerId:" + std::to_string(customerId) + " distance:" + std::to_string(distance) + " status:" + stat + " collectorId:" + std::to_string(collectorId) + " driverId:" + std::to_string(driverId);
    return s;
}
