#include "elevator.h"

elevator::elevator(string name)
{
	theMutex = new CMutex(string("__Mutex") + name);
}


elevator::~elevator()
{
	delete theMutex;
}

void elevator::GetElevatorStatus(){
    // insert stuff here
}

void elevator::WriteToScreen(int x, int y, string input) {
	theMutex->Wait();
	MOVE_CURSOR(x, y);             	// move cursor to cords [x,y] 
	cout << input << " @ " << x << " " << y;
	//printf("%s @ ( %d , %d )", input, x, y);
	cout.flush();
	//fflush(stdout);		      	// force output to be written to screen now
	theMutex->Signal();
	Sleep(500);

}