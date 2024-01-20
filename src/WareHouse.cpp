
#include "../include/WareHouse.h"
#include "../include/Customer.h"
#include "../include/Volunteer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

void WareHouse::ParseConFile(const string &configFilePath)
{
    std::ifstream myfile;
    myfile.open(configFilePath); // getting referese mabye add *
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
        customerCounter--; // problem in the type, so we dont do nothing
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
        volunteerCounter--; // problem in the type, so we dont do nothing
    volunteerCounter++;
}

WareHouse::WareHouse(const string &configFilePath)
{
    isOpen = false;
    customerCounter = 0;
    volunteerCounter = 0;
    ParseConFile(configFilePath);
}

void start();
void addOrder(Order *order);
void addAction(Action *action);

Customer &WareHouse::getCustomer(int customerId) const
{
    for (int i = 0; i < customers.size(); i++)
    {
        if (customers[i]->getId() == customerId)
            return *customers[i];
    }
    std::cout << "Customer was not found" << std::endl;
}

Volunteer &WareHouse::getVolunteer(int volunteerId) const
{
    for (int i = 0; i < volunteers.size(); i++)
    {
        if (volunteers[i]->getId() == volunteerId)
            return *volunteers[i];
    }
    std::cout << "Volunteer was not found" << std::endl;
}

Order &WareHouse::getOrder(int orderId) const {}
const vector<Action *> &WareHouse::getActions() const {};
void close();
void open();
