#include "WashingMachine.h"



WashingMachine::WashingMachine(int num)
{
	WM_number = num;
}


WashingMachine::~WashingMachine()
{
}


int WashingMachine::main() {
	
	//Default start up in CMS_IDLE
	while (cycle) {
		switch (state) {
		case WMS_IDLE: idle();
		case WMS_FILLING: filling();
		case WMS_WASHING: washing();
		case WMS_DRAINING: draining();
		case WMS_SPINNING: spinning();
		default: state = WMS_IDLE;
		}
	}
	return 0;
}

void WashingMachine::idle() {
	printf(" Washing Machine #%d : Ready \n", WM_number);
	Sleep(5);
	state = WMS_FILLING;
}

void WashingMachine::filling() {
	printf(" Washing Machine #%d : filling \n", WM_number);
	Sleep(5);
	state = WMS_WASHING;
}

void WashingMachine::washing() {
	printf(" Washing Machine #%d : washing \n", WM_number);
	Sleep(5);
	state = WMS_DRAINING;
}

void WashingMachine::draining() {
	printf(" Washing Machine #%d : draining \n", WM_number);
	Sleep(5);
	state = WMS_SPINNING;
}

void WashingMachine::spinning() {
	printf(" Washing Machine #%d : spinning \n", WM_number);
	Sleep(5);
	cycle = false;
	state = WMS_IDLE;
}