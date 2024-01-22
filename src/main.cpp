#include "../include/WareHouse.h"
#include "../include/Customer.h"
#include "../include/Volunteer.h"
#include "../include/Order.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <bits/stdc++.h>
// #include "Parse.h"

using namespace std;

// WareHouse* backup = nullptr;

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "usage: warehouse <config_path>" << std::endl;
        return 0;
    }

    string configurationFile = argv[1];
    WareHouse wareHouse(configurationFile);
    for (int i = 0; i < 2; i++)
    {
        Customer &c = wareHouse.getCustomer(i);
        // std::cout << c.getName() + " " + std::to_string(c.getId()) << std::endl;
    }

    for (int i = 0; i < 4; i++)
    {
        Volunteer &v = wareHouse.getVolunteer(i);
        // std::cout << v.toString() << std::endl;
        //  std::cout << v.getName() + " " + std::to_string(v.getId()) << std::endl;
    }
    Customer &c = wareHouse.getCustomer(0);
    Order *o1 = new Order(13, c.getId(), c.getCustomerDistance());
    std::cout << (*o1).toString() << std::endl;
    /*
    wareHouse.start();
    if(backup!=nullptr){
        delete backup;
        backup = nullptr;
    }
    return 0;
    */
}
