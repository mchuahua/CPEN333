#pragma once

#ifndef __CPullLamp__
#define __CPullLamp__

#include "CBulb.h"
#include "CSwitch.h"
#include "CLamp3Bulb.h"

//CPullLamp class

class CPullLamp : public CLamp3Bulb
{
public:
	//Default constructor
	CPullLamp(int w1, int w2, int w3);
	//Deconstructor
	~CPullLamp();
    //Toggle function 
    void toggle();
private:
    void LampOn(){}
    void LampOff(){}
};

#endif