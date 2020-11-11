#include "elevator.h"

elevator::elevator(string name)
{
	// Mutex
	theMutex = new CMutex(string("__Mutex") + name);
	
	// Datapool
    datapool = new CDataPool(string("__Data") + name, sizeof(struct thedata));
	datapool_ptr = (struct thedata*)(datapool->LinkDataPool()); // get pointer to data pool

	// insert stuff here syncrhoinzation
    ps1 = new CSemaphore(string("PS1") + name, 0, 1);    // semaphore with initial value 0 and max value 1
    ps2 = new CSemaphore(string("PS2") + name, 0, 1);    // semaphore with initial value 0 and max value 1
    cs1 = new CSemaphore(string("CS1") + name, 1, 1);    // semaphore with initial value 1 and max value 1
    cs2 = new CSemaphore(string("CS2") + name, 1, 1);    // semaphore with initial value 1 and max value 1

}

elevator::~elevator()
{
	delete theMutex;
	delete datapool;
}

void elevator::set_dest(int floor){
	theMutex->Wait();
	datapool_ptr->dest_floor = floor;
	theMutex->Signal();
}

// Consumer synchronization for dispatcher, p2c2
thedata elevator::dispatcher_syncrhonize(thedata *data){
    CSemaphore      completed("done", 0, 1);

	ps2->Wait() ;		// wait for producer process to signal producer semaphore
	// Read all data from elevator
	data->dest_floor = datapool_ptr -> dest_floor;
	data->curr_floor = datapool_ptr -> curr_floor;
	data->closed = datapool_ptr -> closed;
	data->idle = datapool_ptr -> idle;

	cs2->Signal();	
	
}

// Consumer synchronization for io, p1c1
thedata elevator::io_syncrhonize(thedata *data){
    CSemaphore      completed("done", 0, 1);

	ps2->Wait() ;		// wait for producer process to signal producer semaphore
	if (completed.Read() > 0)
		return;
	// Read all data from elevator
	data->dest_floor = datapool_ptr -> dest_floor;
	data->curr_floor = datapool_ptr -> curr_floor;
	data->closed = datapool_ptr -> closed;
	data->idle = datapool_ptr -> idle;

	cs2->Signal();	

}

// Producer synhcronization
void elevator::GetElevatorStatus(){

    CSemaphore      completed("done", 0, 1);


	while(completed.Read() != 1){
		// Amount of time to sleep in between floors (to simulate floor travelling)
		Sleep(1000); 
		if (completed.Read() > 0 ){
				return;
		}
		// Elevator is the producer, we produce the floors. IO and dispatcher reads the current value
		if (ps1->Read() > 0 && ps2->Read() > 0) {
			cs1->Wait();		// wait for consumer processes to signal producer semaphore
			if (completed.Read()  > 0){
				return;
			}
			cs2->Wait();
			if (completed.Read()  > 0){
				return;
			}
			// Read elevator status, and go up or down depending on what it sees.
			theMutex->Wait();

			if (datapool_ptr->dest_floor == datapool_ptr->curr_floor && datapool_ptr->idle == false){
				if (datapool_ptr->closed){
					datapool_ptr->closed = false;
				}
				else
				{
					datapool_ptr->closed = true;
					datapool_ptr->idle = true;
					return;
				}
			}
			else if (datapool_ptr->dest_floor < datapool_ptr->curr_floor){
				(datapool_ptr->curr_floor)--;
				datapool_ptr->idle = false;
			}
			else if (datapool_ptr->dest_floor > datapool_ptr->curr_floor){
				(datapool_ptr->curr_floor)++;
				datapool_ptr->idle = false;
			}
			theMutex->Signal();	
			
                // Do stuff with io for elevator 1
				// Make sure IO has read the last update
				// Write new data to pool
			ps1->Signal();		// signal the consumer semaphore to wake up the producer
			ps2->Signal();
		}
	}
}

// void elevator::GetElevator2Status(){

//     // insert stuff here syncrhoinzation
//     CSemaphore		ps3("PS3", 0, 1);    // semaphore with initial value 0 and max value 1
// 	CSemaphore		cs3("CS3", 1, 1);    // semaphore with initial value 1 and max value 1
// 	CSemaphore		cs4("CS4", 1, 1);    // semaphore with initial value 1 and max value 1
// 	CSemaphore		ps4("PS4", 0, 1);    // semaphore with initial value 0 and max value 1
//     CSemaphore      completed("done", 0, 1);

// 	// // Elevator 2 datapool
//     // CDataPool dp2("elevator2", sizeof(struct data));
// 	// elevator2status = (struct data*)(dp2.LinkDataPool()); // get pointer to data pool

// 	// while(completed.Read() != 1){
// 	// 	Sleep(500);

//     //     if (ps3.Read() > 0) {
// 	// 		ps3.Wait();		// wait for producer process to signal producer semaphore
//     //             // Do stuff with io for leevator 2
// 	// 		cs3.Signal();		// signal the consumer semaphore to wake up the producer
// 	// 	}
// 	// 	if (ps4.Read() > 0) {
// 	// 		ps4.Wait();		// wait for producer process to signal producer semaphore
//     //             // Do stuff with dispatcher for elevator 2
// 	// 		cs4.Signal();		// signal the consumer semaphore to wake up the producer
// 	// 	}
// 	// }
// }

// Not even needed
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