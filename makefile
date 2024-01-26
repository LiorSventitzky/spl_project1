
all:	clean compile link

link:
	g++ -o bin/run bin/main.o bin/WareHouse.o bin/Customer.o bin/SoldierCustomer.o bin/CivilianCustomer.o bin/Volunteer.o bin/CollectorVolunteer.o bin/LimitedCollectorVolunteer.o bin/DriverVolunteer.o bin/LimitedDriverVolunteer.o bin/Order.o bin/BaseAction.o bin/SimulateStep.o bin/AddOrder.o bin/AddCustomer.o bin/PrintOrderStatus.o bin/PrintCustomerStatus.o bin/PrintVolunteerStatus.o bin/BackupWarehouse.o bin/RestoreWareHouse.o

compile:
	g++ -g -Wall -Weffc++ -c -o bin/main.o src/main.cpp
	g++ -g -Wall -Weffc++ -c -o bin/WareHouse.o src/WareHouse.cpp
	g++ -g -Wall -Weffc++ -c -o bin/Customer.o src/Customer.cpp
	g++ -g -Wall -Weffc++ -c -o bin/SoldierCustomer.o src/SoldierCustomer.cpp
	g++ -g -Wall -Weffc++ -c -o bin/CivilianCustomer.o src/CivilianCustomer.cpp
	g++ -g -Wall -Weffc++ -c -o bin/Volunteer.o src/Volunteer.cpp
	g++ -g -Wall -Weffc++ -c -o bin/CollectorVolunteer.o src/CollectorVolunteer.cpp
	g++ -g -Wall -Weffc++ -c -o bin/LimitedCollectorVolunteer.o src/LimitedCollectorVolunteer.cpp
	g++ -g -Wall -Weffc++ -c -o bin/DriverVolunteer.o src/DriverVolunteer.cpp
	g++ -g -Wall -Weffc++ -c -o bin/LimitedDriverVolunteer.o src/LimitedDriverVolunteer.cpp
	g++ -g -Wall -Weffc++ -c -o bin/Order.o src/Order.cpp
	g++ -g -Wall -Weffc++ -c -o bin/BaseAction.o src/BaseAction.cpp
	g++ -g -Wall -Weffc++ -c -o bin/SimulateStep.o src/SimulateStep.cpp
	g++ -g -Wall -Weffc++ -c -o bin/AddOrder.o src/AddOrder.cpp
	g++ -g -Wall -Weffc++ -c -o bin/AddCustomer.o src/AddCustomer.cpp
	g++ -g -Wall -Weffc++ -c -o bin/PrintOrderStatus.o src/PrintOrderStatus.cpp
	g++ -g -Wall -Weffc++ -c -o bin/PrintCustomerStatus.o src/PrintCustomerStatus.cpp
	g++ -g -Wall -Weffc++ -c -o bin/PrintVolunteerStatus.o src/PrintVolunteerStatus.cpp
	g++ -g -Wall -Weffc++ -c -o bin/BackupWarehouse.o src/BackupWarehouse.cpp
	g++ -g -Wall -Weffc++ -c -o bin/RestoreWareHouse.o src/RestoreWareHouse.cpp
 #	g++ -g -Wall -Weffc++ -c -o bin/Parse.o src/Parse.cpp



clean:
	rm -f bin/*
