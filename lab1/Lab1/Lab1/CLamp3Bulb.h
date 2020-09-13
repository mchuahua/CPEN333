#pragma once

#ifndef __CLamp3Bulb__
#define __CLamp3Bulb__

#include "CBulb.h"
#include "CSwitch.h"
//CLamp3Bulb class

class CLamp3Bulb
{
public:
	//Default constructor
	CLamp3Bulb(int w1, int w2, int w3);
	//Deconstructor
	~CLamp3Bulb();
	//Turn switch and all three bulbs on
    void LampOn();
    // Turn switch and 3 bulbs off 
    void LampOff();
    // print state of lamp, ie on or off 
    void print();
    // returns state of switch in lamp
    int getState();
    // return power currently actually being consumed by lamp based on state 
    int getPower();
    // Bulb exchange
    CBulb* exchange(CBulb* newBulb, int bulbNum);

private:
	//Exercise 3
    // CBulb bulb_arr[3];
    // CSwitch my_switch;

    //Exercise 4
    CBulb* bulb_arr[3];
    CSwitch* my_switch;
};

#endif