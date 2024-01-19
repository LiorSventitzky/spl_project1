#include <iostream>
#include <fstream>
#include <string>
 

 int ParseConFile(String configurationFile){
std::ifstream myfile;
myfile.open("configFileExample.txt");
std::string mystring;
if ( myfile.is_open()) {
while ( myfile ) {
std::getline (myfile, myline);
std::cout << myline << ": " << myfile.tellg() << '\n';
}
}
else {
std::cout << "Couldn't open file\n";
}
return 0;    
  }