
#include "../include/WareHouse.h"
#include "../include/Customer.h"
#include "../include/Volunteer.h"
#include "../include/Order.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <typeinfo>

using namespace std;

extern WareHouse *backup;

WareHouse::WareHouse(const string &configFilePath) : isOpen(false), actionsLog(), volunteers(), pendingOrders(), inProcessOrders(), completedOrders(), customers(), customerCounter(0), volunteerCounter(0), orderCounter(0)
{
    ParseConFile(configFilePath);
}

WareHouse::WareHouse(const WareHouse &other) : isOpen(other.isOpen), actionsLog(), volunteers(), pendingOrders(), inProcessOrders(), completedOrders(), customers(), customerCounter(other.customerCounter), volunteerCounter(other.volunteerCounter), orderCounter(other.orderCounter)
{
    for (std::vector<Customer *>::size_type i = 0; i < other.customers.size(); i++)
    {
        customers.push_back(other.customers[i]->clone());
    }
    for (std::vector<Volunteer *>::size_type i = 0; i < other.volunteers.size(); i++)
    {
        volunteers.push_back(other.volunteers[i]->clone());
    }
    for (std::vector<Order *>::size_type i = 0; i < other.pendingOrders.size(); i++)
    {
        pendingOrders.push_back(other.pendingOrders[i]->clone());
    }
    for (std::vector<Order *>::size_type i = 0; i < other.inProcessOrders.size(); i++)
    {
        inProcessOrders.push_back(other.inProcessOrders[i]->clone());
    }
    for (std::vector<Order *>::size_type i = 0; i < other.completedOrders.size(); i++)
    {
        completedOrders.push_back(other.completedOrders[i]->clone());
    }
    for (std::vector<BaseAction *>::size_type i = 0; i < other.actionsLog.size(); i++)
    {
        actionsLog.push_back(other.actionsLog[i]->clone());
    }
}

void WareHouse::ParseConFile(const string &configFilePath)
{
    std::ifstream myfile;
    myfile.open(configFilePath);
    std::string myline;
    if (myfile.is_open())
    {
        while (myfile)
        {
            std::getline(myfile, myline);
            stringstream temp(myline);
            string word;
            temp >> word;
            if (word == "customer")
                this->addCustomer(&temp);
            if (word == "volunteer")
                this->addVolunteer(&temp);
        }
    }
}

// add a new customer to the customer list
void WareHouse::addCustomer(stringstream *temp)
{
    string name, type, dis, maxOrder;
    (*temp) >> name >> type >> dis >> maxOrder;
    if (type == "soldier")
    {
        customers.push_back(new SoldierCustomer(customerCounter, name, std::stoi(dis), std::stoi(maxOrder)));
    }
    else if (type == "civilian")
        customers.push_back(new CivilianCustomer(customerCounter, name, std::stoi(dis), std::stoi(maxOrder)));
    else
        customerCounter--; // problem in the type, so we don't do anything
    customerCounter++;
}

void WareHouse::addCustomer(Customer *customer)
{
    customers.push_back(customer);
    customerCounter++;
}

// add a new volunteer to the customer list
void WareHouse::addVolunteer(stringstream *temp)
{
    string name, type;
    (*temp) >> name >> type;
    if (type == "collector")
    {
        string cooldown;
        (*temp) >> cooldown;
        volunteers.push_back(new CollectorVolunteer(volunteerCounter, name, std::stoi(cooldown)));
    }
    else if (type == "limited_collector")
    {
        string cooldown, maxOrder;
        (*temp) >> cooldown >> maxOrder;
        volunteers.push_back(new LimitedCollectorVolunteer(volunteerCounter, name, std::stoi(cooldown), std::stoi(maxOrder)));
    }
    else if (type == "driver")
    {
        string maxdis, distancePerStep;
        (*temp) >> maxdis >> distancePerStep;
        volunteers.push_back(new DriverVolunteer(volunteerCounter, name, std::stoi(maxdis), std::stoi(distancePerStep)));
    }
    else if (type == "limited_driver")
    {
        string maxdis, distancePerStep, maxOrder;
        (*temp) >> maxdis >> distancePerStep >> maxOrder;
        volunteers.push_back(new LimitedDriverVolunteer(volunteerCounter, name, std::stoi(maxdis), std::stoi(distancePerStep), std::stoi(maxOrder)));
    }
    else
        volunteerCounter--; // problem in the type, so we don't do anything
    volunteerCounter++;
}

void WareHouse::addOrder(Order *order)
{
    pendingOrders.push_back(order);
    orderCounter++;
}

Customer &WareHouse::getCustomer(int customerId) const
{
    for (std::vector<Customer *>::size_type i = 0; i < customers.size(); i++)
    {
        if (customers[i]->getId() == customerId)
            return *customers[i];
    }
    std::cout << "Customer was not found" << std::endl;
    Customer *c = new SoldierCustomer(-1, "NULL", -1, -1);
    return *c;
}

Volunteer &WareHouse::getVolunteer(int volunteerId) const
{
    for (std::vector<Volunteer *>::size_type i = 0; i < volunteers.size(); i++)
    {
        if (volunteers[i]->getId() == volunteerId)
            return *volunteers[i];
    }
    std::cout << "Volunteer was not found" << std::endl;
    Volunteer *v = new CollectorVolunteer(-1, "NULL", -1);
    return *v;
}

Order &WareHouse::getOrder(int orderId) const
{
    for (std::vector<Order *>::size_type i = 0; i < pendingOrders.size(); i++)
    {
        if (pendingOrders[i]->getId() == orderId)
            return *pendingOrders[i];
    }
    for (std::vector<Order *>::size_type i = 0; i < inProcessOrders.size(); i++)
    {
        if (inProcessOrders[i]->getId() == orderId)
            return *inProcessOrders[i];
    }
    for (std::vector<Order *>::size_type i = 0; i < completedOrders.size(); i++)
    {
        if (completedOrders[i]->getId() == orderId)
            return *completedOrders[i];
    }
    std::cout << "Order was not found" << std::endl;
    Order *o = new Order(-1, -1, -1);
    return *o;
}

void WareHouse::SimulateStepInWarehouse()
{
    /*
    std::cout << "vol!!!!!!" << std::endl;
    for (std::vector<Volunteer*>::size_type i = 0; i < volunteers.size(); i++)
        std::cout << volunteers[i]->toString() << std::endl;
        */
    // 1
    for (std::vector<Order *>::size_type i = 0; i < pendingOrders.size(); i++)
    {
        if ((*pendingOrders[i]).getStatus() == OrderStatus::PENDING)
        {
            if (findAvailableCollector(*pendingOrders[i], i))
                i--;
        }
        else
        {
            if (findAvailableDriver(*pendingOrders[i], i))
                i--;
        }
    }

    // std::cout << "step 1 sus" << std::endl;

    // 2 + 3 + 4
    for (std::vector<Order *>::size_type i = 0; i < volunteers.size(); i++)
    {
        if (volunteers[i]->isBusy())
        {
            // 2
            volunteers[i]->step();
            //   std::cout << volunteers[i]->toString() << std::endl;
            //   std::cout << "step 2 sus" << std::endl;

            // 3
            if (volunteers[i]->getCompletedOrderId() != NO_ORDER)
            {
                for (std::vector<Order *>::size_type j = 0; j < inProcessOrders.size(); j++)
                {
                    if (inProcessOrders[j]->getId() == volunteers[i]->getCompletedOrderId())
                    {
                        if (inProcessOrders[j]->getStatus() == OrderStatus::COLLECTING)
                        {
                            pendingOrders.push_back(inProcessOrders[j]);
                            inProcessOrders.erase(inProcessOrders.begin() + j);
                        }
                        else
                        {
                            completedOrders.push_back(inProcessOrders[j]);
                            inProcessOrders.erase(inProcessOrders.begin() + j);
                        }
                        j = inProcessOrders.size();
                    }
                }
                volunteers[i]->finishCompletedOrder();
            }
            //  std::cout << "step 3 sus" << std::endl;

            // 4
            if ((!volunteers[i]->isBusy()) && !volunteers[i]->hasOrdersLeft())
            {
                delete volunteers[i];
                volunteers.erase(volunteers.begin() + i);
                i--;
            }
            //  std::cout << "step 4 sus" << std::endl;
        }
    }
}

bool WareHouse::findAvailableCollector(Order &order, int index)
{
    int size = volunteers.size();
    for (auto i = 0; i < size; i++)
    {
        if (typeid(*volunteers[i]) == typeid(CollectorVolunteer) || typeid(*volunteers[i]) == typeid(LimitedCollectorVolunteer))
        {
            if ((*volunteers[i]).canTakeOrder(order))
            {
                (*volunteers[i]).acceptOrder(order);
                order.setCollectorId((*volunteers[i]).getId());
                order.setStatus(OrderStatus::COLLECTING);
                inProcessOrders.push_back(&order);
                pendingOrders.erase(pendingOrders.begin() + index);
                return true;
            }
        }
    }
    return false;
}

bool WareHouse::findAvailableDriver(Order &order, int index)
{
    for (std::vector<Volunteer *>::size_type i = 0; i < volunteers.size(); i++)
    {
        if (typeid(*volunteers[i]) == typeid(DriverVolunteer) || typeid(*volunteers[i]) == typeid(LimitedDriverVolunteer))
        {
            if ((*volunteers[i]).canTakeOrder(order))
            {
                (*volunteers[i]).acceptOrder(order);
                order.setDriverId((*volunteers[i]).getId());
                order.setStatus(OrderStatus::DELIVERING);
                inProcessOrders.push_back(&order);
                pendingOrders.erase(pendingOrders.begin() + index);
                return true;
            }
        }
    }
    return false;
}

void WareHouse::addAction(BaseAction *action) { actionsLog.push_back(action); }

const vector<BaseAction *> &WareHouse::getActions() const { return actionsLog; };

int WareHouse::getOrderCounter()
{
    return orderCounter;
}

int WareHouse::getCustomerCounter() { return customerCounter; }

void WareHouse::printOrderStatus(int orderId)
{
    bool found = false;
    for (std::vector<Order *>::size_type i = 0; i < pendingOrders.size() && !found; i++)
    {
        if (pendingOrders[i]->getId() == orderId)
        {
            cout << pendingOrders[i]->toString() + "/n";
            found = true;
        }
    }
    for (std::vector<Order *>::size_type i = 0; i < inProcessOrders.size() && !found; i++)
    {
        if (inProcessOrders[i]->getId() == orderId)
        {
            cout << inProcessOrders[i]->toString() + "/n";
            found = true;
        }
    }
    for (std::vector<Order *>::size_type i = 0; i < completedOrders.size() && !found; i++)
    {
        if (completedOrders[i]->getId() == orderId)
        {
            cout << completedOrders[i]->toString() + "/n";
            found = true;
        }
    }
}

void WareHouse::printCustomerStatus(int customerId)
{
    cout << "CustomerId: " + std::to_string(customerId) + "\n";
    Customer &c = getCustomer(customerId);
    vector<int> ordersId = c.getOrdersIds();
    for (std::vector<Order *>::size_type i = 0; i < ordersId.size(); i++)
    {
        Order &order = getOrder(ordersId[i]);
        cout << order.shortenedToString();
    }
    cout << "numOrdersLeft:" + std::to_string(c.getNumOrders()) + "\n";
}

int WareHouse::doesVolunteerExist(int volunteerId)
{
    for (std::vector<Volunteer *>::size_type i = 0; i < volunteers.size(); i++)
    {
        if (volunteers[i]->getId() == volunteerId)
            return i;
    }
    return -1;
}

void WareHouse::printVolunteerStatus(int index)
{
    Volunteer *v = volunteers[index];
    std::cout << "VolunteerId: " + std::to_string(v->getId()) << std::endl;
    std::cout << "isBusy: " + std::to_string(v->isBusy()) << std::endl;
    if (v->isBusy())
        std::cout << "OrderId " + std::to_string(v->getActiveOrderId()) << std::endl;
    else
        std::cout << "OrderId: NONE" << std::endl;
}

void WareHouse::start() {}

void WareHouse::close() {}

void WareHouse::open()
{
    isOpen = true;
    std::cout << "Warehouse is open!";
}

void WareHouse::createBackUp()
{
    backup = new WareHouse(*this);
}

void WareHouse::restoreWarehouse()
{
    // deep delete
    for (std::vector<Customer *>::size_type i = 0; i < customers.size(); i++)
    {
        delete customers[i];
        customers.erase(customers.begin() + i);
        i--;
    }
    for (std::vector<Volunteer *>::size_type i = 0; i < volunteers.size(); i++)
    {
        delete volunteers[i];
        volunteers.erase(volunteers.begin() + i);
        i--;
    }
    for (std::vector<Order *>::size_type i = 0; i < pendingOrders.size(); i++)
    {
        delete pendingOrders[i];
        pendingOrders.erase(pendingOrders.begin() + i);
        i--;
    }
    for (std::vector<Order *>::size_type i = 0; i < inProcessOrders.size(); i++)
    {
        delete inProcessOrders[i];
        inProcessOrders.erase(inProcessOrders.begin() + i);
        i--;
    }
    for (std::vector<Order *>::size_type i = 0; i < completedOrders.size(); i++)
    {
        delete completedOrders[i];
        completedOrders.erase(completedOrders.begin() + i);
        i--;
    }
    for (std::vector<BaseAction *>::size_type i = 0; i < actionsLog.size(); i++)
    {
        delete actionsLog[i];
        actionsLog.erase(actionsLog.begin() + i);
        i--;
    }
    this->isOpen = backup->isOpen;
    this->customerCounter = backup->customerCounter;
    this->volunteerCounter = backup->volunteerCounter;
    this->orderCounter = backup->orderCounter;
    for (std::vector<Customer *>::size_type i = 0; i < backup->customers.size(); i++)
    {
        customers.push_back((*backup->customers[i]).clone());
    }
    for (std::vector<Volunteer *>::size_type i = 0; i < backup->volunteers.size(); i++)
    {
        volunteers.push_back((*backup->volunteers[i]).clone());
    }
    for (std::vector<Order *>::size_type i = 0; i < backup->pendingOrders.size(); i++)
    {
        pendingOrders.push_back((*backup->pendingOrders[i]).clone());
    }
    for (std::vector<Order *>::size_type i = 0; i < backup->inProcessOrders.size(); i++)
    {
        inProcessOrders.push_back((*backup->inProcessOrders[i]).clone());
    }
    for (std::vector<Order *>::size_type i = 0; i < backup->completedOrders.size(); i++)
    {

        completedOrders.push_back((*backup->completedOrders[i]).clone());
    }
    for (std::vector<Action *>::size_type i = 0; i < backup->actionsLog.size(); i++)
    {
        actionsLog.push_back((*backup->actionsLog[i]).clone());
    }
}

void WareHouse::PrintStuff()
{
    for (std::vector<Customer *>::size_type i = 0; i < volunteers.size(); i++)
        std::cout << volunteers[i]->toString() << std::endl;
}

void WareHouse::PrintWareHouse()
{
    std::cout << "WareHouse:" << std::endl;
    std::cout << "isOpen: " + std::to_string(isOpen) << std::endl;
    std::cout << "" << std::endl;
    std::cout << "customers:" + std::to_string(customerCounter) << std::endl;
    for (std::vector<Customer *>::size_type i = 0; i < customers.size(); i++)
        std::cout << customers[i]->toString() << std::endl;
    std::cout << "" << std::endl;
    std::cout << "volunteers:" + std::to_string(volunteerCounter) << std::endl;
    for (std::vector<Volunteer *>::size_type i = 0; i < volunteers.size(); i++)
        std::cout << volunteers[i]->toString() << std::endl;
    std::cout << "" << std::endl;
    std::cout << "num of orders:" + std::to_string(orderCounter) << std::endl;
    std::cout << "pending orders:" << std::endl;
    for (std::vector<Order *>::size_type i = 0; i < pendingOrders.size(); i++)
        std::cout << pendingOrders[i]->toString() << std::endl;
    std::cout << "" << std::endl;
    std::cout << "processing orders:" << std::endl;
    for (std::vector<Order *>::size_type i = 0; i < inProcessOrders.size(); i++)
        std::cout << inProcessOrders[i]->toString() << std::endl;
    std::cout << "" << std::endl;
    std::cout << "complete orders:" << std::endl;
    for (std::vector<Order *>::size_type i = 0; i < completedOrders.size(); i++)
        std::cout << completedOrders[i]->toString() << std::endl;
    std::cout << "" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "actions:" << std::endl;
    for (std::vector<BaseAction *>::size_type i = 0; i < actionsLog.size(); i++)
        std::cout << actionsLog[i]->toString() << std::endl;
    std::cout << "" << std::endl;
}
