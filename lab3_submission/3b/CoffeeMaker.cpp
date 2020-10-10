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

void CoffeeMaker::tall() {
	if (stop_flag)
		return;
	printf(" Coffee Maker #%d : making tall coffee \n", CM_number);
	Sleep(5000);
	state = CMS_GRANDE;
}

void CoffeeMaker::grande() {
	if (stop_flag)
		return;
	printf(" Coffee Maker #%d : making grande coffee \n", CM_number);
	Sleep(5000);
	state = CMS_VENTI;
}

void CoffeeMaker::venti() {
	if (stop_flag)
		return;
	printf(" Coffee Maker #%d : making venti coffee\n", CM_number);
	
	Sleep(5000);
	state = CMS_IDLE;
	start = false;
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