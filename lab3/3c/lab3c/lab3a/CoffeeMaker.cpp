#include "CoffeeMaker.h"

CoffeeMaker::CoffeeMaker(int num)
{
	CM_number = num;
}


CoffeeMaker::~CoffeeMaker()
{
}

int CoffeeMaker::main() {
	//Default start up in CMS_IDLE
	while (1) {
		if (!stop_flag && start) { //removing this if statement makes switch state proceed even if state is always IDLE ??????
			switch (state) {
			case CMS_IDLE: idle();
			case CMS_TALL: tall();
			case CMS_GRANDE: grande();
			case CMS_VENTI: venti();
			default: state = CMS_IDLE;
			}
		}
		Sleep(100);
	}
	return 0;
}

void CoffeeMaker::idle() {
	

	if (start == true && stop_flag == false) {
		printf(" Coffee Maker #%d : Ready to make three coffees \n", CM_number);
		Sleep(5000);
		state = CMS_TALL;
	}
	else {
		Sleep(2000);
		state = CMS_IDLE;
	}

}

void grinding(int num) {
	printf("Grinding coffee beans for CM%d ....\n", num);
	Sleep(1000);
	printf("Done grinding coffee beans for CM%d\n", num);
}

void watering(int num) {
	printf("Brewing coffee then pouring for CM%d ....\n", num);
	Sleep(1000);
	printf("Done brewing and pouring for CM%d\n", num);
}
void milking(int num) {
	printf("Adding milk and cream for CM%d ....\n", num);
	Sleep(1000);
	printf("Done adding milk and cream or CM%d\n", num);
}

void CoffeeMaker::tall() {
	if (stop_flag)
		return;
	printf(" Coffee Maker #%d : making tall coffee \n", CM_number);
	grind = new thread(grinding, CM_number);
	water = new thread(watering, CM_number);
	milkcream = new thread(milking, CM_number);
	Sleep(5000);
	state = CMS_GRANDE;

	grind->join();
	water->join();
	milkcream->join();
	delete grind;
	delete water;
	delete milkcream;
}

void CoffeeMaker::grande() {
	if (stop_flag)
		return;

	printf(" Coffee Maker #%d : making grande coffee \n", CM_number);
	grind = new thread(grinding, CM_number);
	water = new thread(watering, CM_number);
	milkcream = new thread(milking, CM_number);
	Sleep(5000);
	state = CMS_VENTI;
	grind->join();
	water->join();
	milkcream->join();
	delete grind;
	delete water;
	delete milkcream;
}

void CoffeeMaker::venti() {
	if (stop_flag)
		return;
	printf(" Coffee Maker #%d : making venti coffee\n", CM_number);
	grind = new thread(grinding, CM_number);
	water = new thread(watering, CM_number);
	milkcream = new thread(milking, CM_number);
	Sleep(5000);
	state = CMS_IDLE;
	start = false;
	grind->join();
	water->join();
	milkcream->join();
	delete grind;
	delete water;
	delete milkcream;
}

void CoffeeMaker::Start() {
	if (start == true)
		printf("Coffee maker already running!");
	else {
		start = true;
		stop_flag = false;
		printf("Started Coffee Maker #%d\n", CM_number);
	}
}

void CoffeeMaker::Stop() {
	if (start = false)
		printf("Coffee maker already stopped!");
	else {
		start = false;
		stop_flag = true;
		state = CMS_IDLE;
		printf("Stopped Coffee Maker #%d\n", CM_number);
	}
}