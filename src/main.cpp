#include "../include/WareHouse.h"
#include "../include/Customer.h"
#include "../include/Volunteer.h"
#include "../include/Order.h"
#include "../include/Action.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <bits/stdc++.h>
// #include "Parse.h"

using namespace std;

WareHouse *backup = nullptr;

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "usage: warehouse <config_path>" << std::endl;
        return 0;
    }

    string configurationFile = argv[1];
    WareHouse wareHouse(configurationFile);

    /*
        for (int i = 0; i < 2; i++)
        {
            Customer &c = wareHouse.getCustomer(i);
            // std::cout << c.getName() + std::to_string(c.getId()) << std::endl;
        }

        for (int i = 0; i < 4; i++)
        {
            Volunteer &v = wareHouse.getVolunteer(i);
            //  std::cout << v.toString() << std::endl;
            //  std::cout << v.getName() + " " + std::to_string(v.getId()) << std::endl;
        }
        Customer &c = wareHouse.getCustomer(0);
        Customer &c1 = wareHouse.getCustomer(1);
        Order *o1 = new Order(13, c.getId(), c.getCustomerDistance());
        Order *o2 = new Order(14, c1.getId(), c1.getCustomerDistance());
        Order *o3 = new Order(15, c.getId(), c.getCustomerDistance());
        Order *o4 = new Order(16, c.getId(), c.getCustomerDistance());

        wareHouse.addOrder(o1);
        wareHouse.addOrder(o2);
        wareHouse.addOrder(o3);
        wareHouse.addOrder(o4);
    */

    AddOrder *od1 = new AddOrder(0);
    (*od1).act(wareHouse);
    AddOrder *od2 = new AddOrder(0);
    (*od2).act(wareHouse);
    AddOrder *od3 = new AddOrder(0);
    (*od3).act(wareHouse);
    // wareHouse.addOrder(o1);

    AddCustomer *ac1 = new AddCustomer("a", "soldier", 2, 3);
    ac1->act(wareHouse);
    AddCustomer *ac2 = new AddCustomer("b", "soldier", 10, 2);
    ac2->act(wareHouse);
    AddCustomer *ac3 = new AddCustomer("c", "civilian", 5, 5);
    ac3->act(wareHouse);
    AddCustomer *ac4 = new AddCustomer("d", "soldier", 6, 3);
    ac4->act(wareHouse);
    AddCustomer *ac5 = new AddCustomer("e", "civilian", 2, 1);
    ac5->act(wareHouse);

    std::cout << "" << std::endl;
    std::cout << "" << std::endl;

    // SimulateStep *s = new SimulateStep(20);
    // s->act(wareHouse);
    // wareHouse.PrintStuff();

    // PrintCustomerStatus *p = new PrintCustomerStatus(0);
    // p->act(wareHouse);

    // backup and restore
    SimulateStep *s = new SimulateStep(5);
    s->act(wareHouse);
    BackupWareHouse *b = new BackupWareHouse();
    b->act(wareHouse);
    AddOrder *od4 = new AddOrder(1);
    (*od4).act(wareHouse);
    SimulateStep *s1 = new SimulateStep(6);
    s1->act(wareHouse);

    wareHouse.PrintWareHouse();
    std::cout << "" << std::endl;
    std::cout << "////////////back up//////////////" << std::endl;
    backup->PrintWareHouse();
    std::cout << "" << std::endl;
    std::cout << "////////////retore///////////////" << std::endl;
    RestoreWareHouse *r = new RestoreWareHouse();
    r->act(wareHouse);
    wareHouse.PrintWareHouse();

    wareHouse.PrintStuff();

    //   std::cout << o2->toString() << std::endl;
    //   std::cout << o3->toString() << std::endl;
    //  std::cout << o4->toString() << std::endl;

    wareHouse.start();
    if (backup != nullptr)
    {
        delete backup;
        backup = nullptr;
    }
    return 0;
}
