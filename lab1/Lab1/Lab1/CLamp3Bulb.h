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
	
private:
	CBulb* bulb_arr[3];
    CSwitch my_switch;
};

#endif