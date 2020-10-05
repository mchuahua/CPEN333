#pragma once

#include "../../../../RTExamples/rt.h"

//WMS -> Washing Machine State
enum {
	WMS_IDLE,
	WMS_FILLING,
	WMS_DRAINING,
	WMS_SPINNING
};

class WashingMachine : public ActiveClass
{
public:
	WashingMachine(int num);
	~WashingMachine();
private:
	int main();
	void idle();

	int WM_number;
	int state = WMS_IDLE;
};

