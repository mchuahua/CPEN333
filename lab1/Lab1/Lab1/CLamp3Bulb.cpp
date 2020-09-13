#include "CLamp3Bulb.h"
#include <iostream>

//Default Constructor with three inputs. Constructs lamp and sets wattage of three bulbs, with state off
CLamp3Bulb::CLamp3Bulb(int w1, int w2, int w3){
	
    // Exercise 3
    // bulb_arr[0].setwatts(w1);
	// bulb_arr[1].setwatts(w2);
	// bulb_arr[2].setwatts(w3);
    
    // Exercise 4
    bulb_arr[0] = new CBulb(w1);
	bulb_arr[1] = new CBulb(w2);
	bulb_arr[2] = new CBulb(w3);
    my_switch = new CSwitch();

	std::cout << "CLamp3Bulb default Constructor is being called.." << std::endl;
}

//Deconstructor
CLamp3Bulb::~CLamp3Bulb(){
    // Exercise 4
    delete bulb_arr[0];
    delete bulb_arr[1];
    delete bulb_arr[2];
    delete my_switch;
	std::cout << "CLamp3Bulb destructor being called.." << std::endl;
}

// Copy constructor 
CLamp3Bulb::CLamp3Bulb(const CLamp3Bulb &copy){
    bulb_arr[0] = new CBulb;
    bulb_arr[1] = new CBulb;
    bulb_arr[2] = new CBulb;
    my_switch   = new CSwitch;

    *bulb_arr[0] = *copy.bulb_arr[0];
    *bulb_arr[1] = *copy.bulb_arr[2];
    *bulb_arr[2] = *copy.bulb_arr[3];
    *my_switch = *copy.my_switch;
}

//Turn switch and all three bulbs on
void CLamp3Bulb::LampOn(){
    // Turn switch on
    // Exercise 3
    // my_switch.turnon();
    // Exercise 4
    my_switch->turnon();
    
    //Turn all bulbs on
    for (int i = 0; i < 3; ++i){
        // Exercise 3
        // bulb_arr[i].on();
        // Exercise 4
        bulb_arr[i]->on();
    }
}

// Turn switch and 3 bulbs off 
void CLamp3Bulb::LampOff(){
    //Turn switch off 
    // Exercise 3
    // my_switch.turnoff();
    // Exercise 4
    my_switch->turnoff();
    //Turn all bulbs off 
    for (int i = 0; i < 3; ++i){
        // Exercise 3
        // bulb_arr[i].off();
        // Exercise 4
        bulb_arr[i]->off();
    }
}

// print state of lamp, ie on or off 
void CLamp3Bulb::print(){
    // Exercise 3
    // my_switch.print();
    // Exercise 4
    my_switch->print();

}

// returns state of switch in lamp
int CLamp3Bulb::getState(){
    // Exercise 3
    // return my_switch.getState();
    // Exercise 4
    return my_switch->getState();
}

// return power currently actually being consumed by lamp based on state 
int CLamp3Bulb::getPower(){
    int total_power = 0;
    //Adds all power used by bulbs if switch is on
    // Exercise 3
    // if (my_switch.getState() != 0){
    //     for (int i = 0; i < 3; ++i){
    //         total_power += bulb_arr[i].getPower();
    //     }
    // Exercise 4
    if (my_switch->getState() != 0){
        for (int i = 0; i < 3; ++i){
            total_power += bulb_arr[i]->getPower();
        }
        
    }
     
    return total_power;
}

CBulb* CLamp3Bulb::exchange(CBulb* newBulb, int bulbNum){
    if (bulbNum < 0 || bulbNum > 2){
        std::cout << "ERROR, bulb number is not in range!" << std::endl;
        return NULL;
    }
    bool lamp_was_on = false;
    //Turn off lamp + bulbs first before exchanging if lamp is on
    if (my_switch->getState() == 1){
        LampOff();
        lamp_was_on = true;
    }
    //Temporary old bulb to return
    CBulb* oldBulb = bulb_arr[bulbNum];

    bulb_arr[bulbNum] = newBulb;

    //Turn lamp + bulbs back on if it was on previously
    if (lamp_was_on)
        LampOn();

    return oldBulb;
}