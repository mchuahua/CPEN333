#pragma once

#include "../../../../RTExamples/rt.h"

//CMS -> Coffee Maker State
enum {
	CMS_IDLE,
	CMS_TALL,
	CMS_GRANDE,
	CMS_VENTI
};

class CoffeeMaker : public ActiveClass
{
public:
	CoffeeMaker(int num);
	~CoffeeMaker();
	void Start();
	void Stop();
private:
	int main();
	void idle();
	void tall();
	void grande();
	void venti();

	int CM_number;
	bool start = true;
	bool stop_flag = false;
	int state = CMS_IDLE;
};

