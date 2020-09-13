//Main
#include "CBulb.h"
#include "CSwitch.h"
#include "CLamp3Bulb.h"
#include "CPullLamp.h"
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
	// CLamp3Bulb my_lamp(100, 100, 100);
	// CBulb* b1 = new CBulb(60);
	// b1 = my_lamp.exchange(b1, 0);
	// delete b1;

	// Exercise 5 - Deep copy
	// CLamp3Bulb my_lamp(100, 100, 100);
	// CLamp3Bulb my_lamp_copy(my_lamp);
	// my_lamp.print();
	// my_lamp.LampOn();
	// my_lamp.print();
	// my_lamp_copy.print();
	// CBulb* b1 = new CBulb(60);
	// b1 = my_lamp.exchange(b1, 1);
	// delete b1;
	// std::cout << "Original lamp power is " << my_lamp.getPower() << std::endl;
	// std::cout << "Copied lamp power is " << my_lamp_copy.getPower() << " because it was deep copied" << std::endl;

	// Exercise 6 - Inheritance
	CPullLamp my_lamp(100, 100, 100);
	// 	my_lamp.LampOn() ;
	// 	std::cout << "Power of Lamp = " << my_lamp.getPower() << std::endl;	// print power
	// 	CBulb *b1 = new CBulb(50);			// create new 50 watt bulb
	// 	b1 = my_lamp.exchange(b1 , 0) ;			// swap bulb 0 for 50 watt bulb
	// 	delete b1;					// delete the old bulb
	//  std::cout << "Power of Lamp = " << my_lamp.getPower() << std::endl;// print power (250 watts)
	// 	my_lamp.LampOff() ;
	//  std::cout << "Power of Lamp = " << my_lamp.getPower() << std::endl;	// print power

	my_lamp.toggle();
	std::cout << "Power of Lamp is " << my_lamp.getPower() << std::endl;
	my_lamp.toggle();
	std::cout << "Power of Lamp is " << my_lamp.getPower() << std::endl;


	return 0;
}

