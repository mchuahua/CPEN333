#pragma once

#include "../../../../RTExamples/rt.h"

//WMS -> Washing Machine State
enum {
	WMS_IDLE,
	WMS_FILLING,
	WMS_WASHING,
	WMS_DRAINING,
	WMS_SPINNING
};

class WashingMachine : public ActiveClass
{
public:
	WashingMachine(int num);
	~WashingMachine();
	void Start();
	void Stop();
private:
	int main();
	void idle();
	void filling();
	void washing();
	void draining();
	void spinning();

	int WM_number;
	bool start = true;
	bool stop_flag = false;
	int state = WMS_IDLE;
};

