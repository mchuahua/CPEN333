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
	while (1) {
		if (!stop_flag && start) {
			switch (state) {
			case WMS_IDLE: idle();
			case WMS_FILLING: filling();
			case WMS_WASHING: washing();
			case WMS_DRAINING: draining();
			case WMS_SPINNING: spinning();
			default: state = WMS_IDLE;
			}
		}
		Sleep(100);
	}
	return 0;
}

void WashingMachine::idle() {

	
	if (start == true && stop_flag == false) {
		printf(" Washing Machine #%d : Ready \n", WM_number);
		Sleep(5000);
		state = WMS_FILLING;
	}
	else {
		Sleep(2000);
		state = WMS_IDLE;
	}

}

void WashingMachine::filling() {
	if (stop_flag)
		return;
	printf(" Washing Machine #%d : filling \n", WM_number);

	Sleep(5000);
	state = WMS_WASHING;
}

void WashingMachine::washing() {
	if (stop_flag)
		return;
	printf(" Washing Machine #%d : washing \n", WM_number);
	Sleep(5000);
	state = WMS_DRAINING;

}

void WashingMachine::draining() {
	if (stop_flag)
		return;
	printf(" Washing Machine #%d : draining \n", WM_number);
	
	Sleep(5000);
	state = WMS_SPINNING;
}

void WashingMachine::spinning() {
	if (stop_flag)
		return;
	printf(" Washing Machine #%d : spinning \n", WM_number);
	start = false;
	
	Sleep(5000);
	state = WMS_IDLE;
}

void WashingMachine::Start() {
	if (start == true)
		printf("Washing machine already running!");
	else {
		start = true;
		stop_flag = false;
		printf("Started Washing Machine #%d\n", WM_number);
	}
}

void WashingMachine::Stop() {
	if (start == false)
		printf("Washing machine already stopped!");
	else {
		start = false;
		stop_flag = true;
		printf("Stopped Washing Machine #%d\n", WM_number);
		state = WMS_IDLE;
	}
}