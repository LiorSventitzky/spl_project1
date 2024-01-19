#pragma once
#include <string>
#include <vector>
#include <sstream>

#include "Order.h"
#include "Customer.h"
#include "Volunteer.h"

#ifndef WareHouse_H_
#define WareHouse_H_

class Action;
class Volunteer;

using namespace std;

// Warehouse responsible for Volunteers, Customers Actions, and Orders.

class WareHouse
{

public:
    WareHouse(const string &configFilePath);
    void start();
    void addOrder(Order *order);
    void addAction(Action *action);
    Customer &getCustomer(int customerId) const;
    Volunteer &getVolunteer(int volunteerId) const;
    Order &getOrder(int orderId) const;
    const vector<Action *> &getActions() const;
    void close();
    void open();

private:
    bool isOpen;
    vector<Action *> actionsLog;
    vector<Volunteer *> volunteers;
    vector<Order *> pendingOrders;
    vector<Order *> inProcessOrders;
    vector<Order *> completedOrders;
    vector<Customer *> customers;
    int customerCounter;  // For assigning unique customer IDs
    int volunteerCounter; // For assigning unique volunteer IDs
    int orderCounter;     // For assigning unique order IDs
    void ParseConFile(const string &configFilePath);
    void addCustomer(stringstream *temp);
    void addVolunteer(stringstream *temp);
};

#endif
