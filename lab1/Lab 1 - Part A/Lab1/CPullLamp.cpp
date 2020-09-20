#include "CPullLamp.h"
#include "CLamp3Bulb.h"
#include <iostream>

// Default constructor
CPullLamp::CPullLamp(int w1, int w2, int w3) : CLamp3Bulb(w1, w2, w3){
    std::cout << "CPullLamp constructor called" << std::endl;
}

// Destructor
CPullLamp::~CPullLamp(){
    std::cout << "Destructor of CPullLamp called" << std::endl;
}


//Toggle function
void CPullLamp::toggle(){
    // turn on/off CPulledLamp using baseclass function lampon / lampoff
    if (getState() == 0)	
		CLamp3Bulb::LampOn();
	else
		CLamp3Bulb::LampOff();

}