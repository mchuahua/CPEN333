#pragma once

#ifndef __CBulb__
#define __CBulb__

//CBulb class

class CBulb
{
public:
	//Default constructor
	CBulb();
	//Constructor for input watts
	CBulb(int input_watts);
	//Deconstructor
	~CBulb();
	//Print function
	void print();
	//Set state function
	//void setstate(bool set_state);
	//Turn on function
	void on();
	//Turn off function
	void off();
	//Get state function
	int getState();
	//set wattage function
	void setwatts(int wattage);
	//Get power function
	int getPower();
private:
	int state;
	int watts;
};

#endif