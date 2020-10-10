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
	while (start) {
		switch (state) {
		case CMS_IDLE: idle();
		case CMS_TALL: tall();
		case CMS_GRANDE: grande();
		case CMS_VENTI: venti();
		default: state = CMS_IDLE;
		}
	}
	return 0;
}

void CoffeeMaker::idle() {
	printf(" Coffee Maker #%d : Ready to make three coffees \n", CM_number);
	Sleep(5);
	state = CMS_TALL;
}

void CoffeeMaker::tall() {
	printf(" Coffee Maker #%d : making tall coffee \n", CM_number);
	Sleep(5);
	state = CMS_GRANDE;
}

void CoffeeMaker::grande() {
	printf(" Coffee Maker #%d : making grande coffee \n", CM_number);
	Sleep(5);
	state = CMS_VENTI;
}

void CoffeeMaker::venti() {
	printf(" Coffee Maker #%d : making venti coffee\n", CM_number);
	Sleep(5);
	state = CMS_IDLE;
	start = false;
}