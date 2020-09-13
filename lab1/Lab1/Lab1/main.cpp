//Main
#include "CBulb.h"
#include "CSwitch.h"
#include "CLamp3Bulb.h"
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
	// CSwitch my_switch;
	// my_switch.print();
	// my_switch.turnon();
	// my_switch.print();
	// if (my_switch.getState() == 1)
	// 	std::cout << "switch is on" << std::endl;
	// my_switch.turnoff();
	// my_switch.print();
	// if (my_switch.getState() == 0)
	// 	std::cout << "switch is off" << std::endl;
	
	// Exercise 3 - CLamp3Bulb
	// int state, power;
	// CLamp3Bulb my_lamp(10, 20, 30);
	// my_lamp.print();
	// power = my_lamp.getPower();
	// std::cout << "Main.cpp power of lamp is " << power << std::endl;
	// state = my_lamp.getState();
	// std::cout << "Main.cpp state of lamp is " << state << std::endl;
	// my_lamp.LampOn();
	// power = my_lamp.getPower();
	// std::cout << "Main.cpp power of lamp is " << power << std::endl;
	// state = my_lamp.getState();
	// std::cout << "Main.cpp state of lamp is " << state << std::endl;
	// my_lamp.print();
	// my_lamp.LampOff();
	// power = my_lamp.getPower();
	// std::cout << "Main.cpp power of lamp is " << power << std::endl;
	// state = my_lamp.getState();
	// std::cout << "Main.cpp state of lamp is " << state << std::endl;
	// my_lamp.print();

	// Exercise 4 - Bulb exchange
	CLamp3Bulb my_lamp(100, 100, 100);
	CBulb* b1 = new CBulb(60);
	b1 = my_lamp.exchange(b1, 0);
	delete b1;

	return 0;
}

