#include "CBulb.h"
#include <iostream>

//Default Constructor initializes all to 0;
CBulb::CBulb(){
	state = 0;
	watts = 0;
	std::cout << "CBulb default Constructor is being called.." << std::endl;
}

//Constructor that takes in input watts
CBulb::CBulb(int input_watts) {
	state = 0;
	watts = input_watts;
	std::cout <<"CBlub input watts Constructor is being called.." << std::endl;
}
//Deconstructor
CBulb::~CBulb(){
	std::cout <<"CBulb desctructor being called.." << std::endl;
}
//Prints numeric value of private var state
void CBulb::print() {
	if (state)
		std::cout << "on" << std::endl;
	else
		std::cout << "off" << std::endl;
}

/*
//Sets state of the bulb
void CBulb::setstate(bool set_state) {
	if (set_state)
		state = 1;
	else
		state = 0;
}
*/
//Turn on bulb state
void CBulb::on() {
	state = 1;
}

//Turn off bulb state
void CBulb::off() {
	state = 0;
}

//Get state function
int CBulb::getState() {
	return state;
}

//Set wattage of bulb function
void CBulb::setwatts(int wattage){
	watts = wattage;
}

//Return power of bulb if bulb is on
int CBulb::getPower(){
	return (state == 0) ? 0 : watts;
}