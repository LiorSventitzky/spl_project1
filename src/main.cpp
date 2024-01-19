#include "../include/WareHouse.h"
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
        std::cout << c.getName() << std::endl;
    }
    /*
    wareHouse.start();
    if(backup!=nullptr){
        delete backup;
        backup = nullptr;
    }
    return 0;
    */
}
