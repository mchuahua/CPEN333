#include "CLamp3Bulb.h"
#include <iostream>

//Default Constructor with three inputs
CLamp3Bulb::CLamp3Bulb(int w1, int w2, int w3){
	state = 0;
	watts = 0;
	std::cout << "CBulb default Constructor is being called.." << std::endl;
}


//Deconstructor
CLamp3Bulb::~CLamp3Bulb(){
	std::cout <<"CLamp3Bulb desctructor being called.." << std::endl;
}
