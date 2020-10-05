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
	switch (state) {
		case WMS_IDLE: idle();
		default: state = WMS_IDLE;
	}

	return 0;
}

void WashingMachine::idle() {
	//cout << "Washing Machine #" << WM_number << " : Ready :" << endl;
	printf(" Washing Machine #%d : Ready: \n", WM_number);
}