#pragma once

#ifndef __CSwitch__
#define __CSwitch__

//CSwitch class

class CSwitch
{
public:
	//Default constructor
	CSwitch();
	//Deconstructor
	~CSwitch();
    //Turn switch on
    void turnon();
    //Turn switch off
    void turnoff();
    //return switch state
    int getState();
    //print state of switch
    void print();
	
private:
    int state;
};

#endif
