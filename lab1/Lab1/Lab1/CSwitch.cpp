#include "CSwitch.h"
#include <iostream>

// Default constructor
CSwitch::CSwitch(){
    // Initializes switch to off
    state = 0;
    std::cout << "CSWitch constructor being called" << std::endl;
}

// Destructor
CSwitch::~CSwitch(){
    std::cout << "CSwitch Destructor being called..." << std::endl;
}

//Turn switch on
void CSwitch::turnon(){
    state = 1;
}

//Turn switch off
void CSwitch::turnoff(){
    state = 0;
}   

//return switch state
int CSwitch::getState(){
    return state;
}

//print state of switch
void CSwitch::print(){
    if (state)
        std::cout << "Switch is on" << std::endl;
    else
    {
        std::cout << "Switch is off" << std::endl;
    }
    
}

