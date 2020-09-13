//Main
#include "CBulb.h"
#include "CSwitch.h"
#include <iostream>

int main()
{
	// Exercise 1 - CBulb
	/*
	int watts = 100;
	int curr_pow;
    //CBulb instance
	CBulb my_bulb(100);
	curr_pow = my_bulb.getPower();
	std::cout << "Current power is " << curr_pow << std::endl;
	my_bulb.on();
	curr_pow = my_bulb.getPower();
	std::cout << "Current power is " << curr_pow << std::endl;
	// my_bulb.on();
	// my_bulb.print();
	// if (my_bulb.getState())
	// 	std::cout << "bulb is on" << std::endl;
	// my_bulb.off();
	// if (!my_bulb.getState())
	// 	std::cout << "bulb is off" << std::endl;
	*/

	// Exercise 2 - CSwitch
	CSwitch my_switch;
	my_switch.print();
	my_switch.turnon();
	my_switch.print();
	if (my_switch.getState() == 1)
		std::cout << "switch is on" << std::endl;
	my_switch.turnoff();
	my_switch.print();
	if (my_switch.getState() == 0)
		std::cout << "switch is off" << std::endl;
	


	return 0;
}

