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

    // insert stuff here syncrhoinzation
    CSemaphore		ps1("PS1", 0, 1);    // semaphore with initial value 0 and max value 1
	CSemaphore		cs1("CS1", 1, 1);    // semaphore with initial value 1 and max value 1
	CSemaphore		cs2("CS2", 1, 1);    // semaphore with initial value 1 and max value 1
	CSemaphore		ps2("PS2", 0, 1);    // semaphore with initial value 0 and max value 1
    CSemaphore		ps3("PS3", 0, 1);    // semaphore with initial value 0 and max value 1
	CSemaphore		cs3("CS3", 1, 1);    // semaphore with initial value 1 and max value 1
	CSemaphore		cs4("CS4", 1, 1);    // semaphore with initial value 1 and max value 1
	CSemaphore		ps4("PS4", 0, 1);    // semaphore with initial value 0 and max value 1
    CSemaphore      completed("done", 0, 1);

    CDataPool dp1("elevator1", sizeof(struct data));
	elevator1status = (struct data*)(dp1.LinkDataPool()); // get pointer to data pool

    CDataPool dp2("elevator2", sizeof(struct data));
	elevator2status = (struct data*)(dp2.LinkDataPool()); // get pointer to data pool

	while(completed.Read() != 1){
		Sleep(500);

		if (ps1.Read() > 0) {
			ps1.Wait();		// wait for producer process to signal producer semaphore
                // Do stuff with io for elevator 1
			cs1.Signal();		// signal the consumer semaphore to wake up the producer
		}
		if (ps2.Read() > 0) {
			ps2.Wait();		// wait for producer process to signal producer semaphore
                // Do stuff with dispatcher for elevator 1
			cs2.Signal();		// signal the consumer semaphore to wake up the producer
		}
        if (ps3.Read() > 0) {
			ps3.Wait();		// wait for producer process to signal producer semaphore
                // Do stuff with io for leevator 2
			cs3.Signal();		// signal the consumer semaphore to wake up the producer
		}
		if (ps4.Read() > 0) {
			ps4.Wait();		// wait for producer process to signal producer semaphore
                // Do stuff with dispatcher for elevator 2
			cs4.Signal();		// signal the consumer semaphore to wake up the producer
		}
	}
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