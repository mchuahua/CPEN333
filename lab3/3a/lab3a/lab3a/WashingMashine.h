#pragma once

#include "../../../../RTExamples/rt.h"

//WMS -> Washing Machine State
enum {
	WMS_IDLE,
	WMS_FILLING,
	WMS_DRAINING,
	WMS_SPINNING
};

class WashingMashine : ActiveClass
{
public:
	WashingMashine();
	~WashingMashine();
private:
	void main();
};

