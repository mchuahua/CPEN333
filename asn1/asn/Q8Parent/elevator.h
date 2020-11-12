#pragma once
#include "../rt.h"
#include <string>
#include <vector>
#include <algorithm>

#define ELEVATOR1 1
#define ELEVATOR2 2

const CMutex console("M1");

struct thedata {
	int dest_floor = 0; //end point
//	int destinations[10]; // put in end point, and also the other floors
	int curr_floor = 0;
	bool closed = true;
	bool idle = true;
	bool up = true;
	bool fault = false;
};

// struct thedata *elevator1status;
// struct thedata *elevator2status;
// No need for active class 
class elevator //: public ActiveClass
{
public:
	elevator(string name);
	~elevator();
	//void GetElevator2Status();
	void GetElevatorStatus(thedata &data);
	void set_dest(int floor);
	void GetElevatorStatus_dispatcher(thedata *data);
	void GetElevatorStatus_io(thedata *data);
	void WriteToConsole(int x, int y);
	void Update_Status(thedata *data);

private:
	void WriteToScreen(int x, int y, string input);

	CMutex *theMutex;
	CDataPool *datapool;
	struct thedata* datapool_ptr;

	CSemaphore *ps1;
	CSemaphore *ps2;
	CSemaphore *cs1;
	CSemaphore *cs2;
};

UINT encode(int curr, int dest, bool idle, bool closed, bool up, bool fault);

thedata decode(UINT message);
