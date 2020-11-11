#pragma once
#include "../rt.h"
#include <string>

struct data {
	int dest_floor;
	int curr_floor;
	bool openclosed;
};

struct data *elevator1status;
struct data *elevator2status;
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
	// int main();
	CMutex *theMutex;
	void GetElevatorStatus();
};

