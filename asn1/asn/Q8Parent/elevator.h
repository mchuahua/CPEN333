#pragma once
#include "../rt.h"
#include <string>

// No need for active class 
class elevator //: public ActiveClass
{
public:
	elevator(string name);
	~elevator();
	// int __thiscall Child1(void *args);

private:
	void WriteToScreen(int x, int y, string input);
	//UINT __stdcall Child(void *args);
	CMutex *theMutex;
	void GetElevatorStatus();
};

