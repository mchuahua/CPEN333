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
	switch (state) {
		case CMS_IDLE: idle();
		case CMS_TALL:
		case CMS_GRANDE:
		case CMS_VENTI:
		default: state = CMS_IDLE;
	}
	return 0;
}

void CoffeeMaker::idle() {
	//cout << "Coffee Maker #" << CM_number << " : Ready :" << endl;
	printf(" Coffee Maker #%d : Ready: \n", CM_number);
}

void CoffeeMaker::tall() {

}

void CoffeeMaker::grande() {

}

void CoffeeMaker::venti() {

}