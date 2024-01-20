
all:	clean compile link

link:
#   g++ -o bin/runner bin/main.o bin/Action.o bin/WareHouse.o bin/Customer.o bin/Volunteer.o bin/Parse.o
	g++ -o bin/run bin/main.o bin/WareHouse.o bin/Customer.o bin/SoldierCustomer.o bin/CivilianCustomer.o bin/Volunteer.o bin/CollectorVolunteer.o bin/LimitedCollectorVolunteer.o bin/DriverVolunteer.o bin/LimitedDriverVolunteer.o

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
 #	g++ -g -Wall -Weffc++ -c -o bin/Order.o src/Order.cpp
 #	g++ -g -Wall -Weffc++ -c -o bin/Parse.o src/Parse.cpp
 #	g++ -g -Wall -Weffc++ -c -o bin/Action.o src/Action.cpp


clean:
	rm -f bin/*
