#pragma once

#include "../../../../RTExamples/rt.h"

//CMS -> Coffee Maker State
enum {
	CMS_IDLE,
	CMS_TALL,
	CMS_GRANDE,
	CMS_VENTI
};

class CoffeeMaker : ActiveClass
{
public:
	CoffeeMaker();
	~CoffeeMaker();
private:
	void main();
};

