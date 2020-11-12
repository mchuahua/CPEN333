#include "elevator.h"

// Constructor for elevator object class.
// Both elevator processes should construct one with a different name such that it'll be independently controlled.
elevator::elevator(string name)
{
	// Mutex
	theMutex = new CMutex(string("__Mutex") + name);
	
	// Datapool
    datapool = new CDataPool(string("__Data") + name, sizeof(struct thedata));
	datapool_ptr = (struct thedata*)(datapool->LinkDataPool()); // get pointer to data pool

	// syncrhoinzation semaphores for producer / consumer
    ps1 = new CSemaphore(string("PS1") + name, 0, 1);    // semaphore with initial value 0 and max value 1
    ps2 = new CSemaphore(string("PS2") + name, 0, 1);    // semaphore with initial value 0 and max value 1
    cs1 = new CSemaphore(string("CS1") + name, 1, 1);    // semaphore with initial value 1 and max value 1
    cs2 = new CSemaphore(string("CS2") + name, 1, 1);    // semaphore with initial value 1 and max value 1
}

// Destructor and deletes all dynamically allocated variables
elevator::~elevator()
{
	delete theMutex;
	delete datapool;
	delete ps1;
	delete ps2;
	delete cs1;
	delete cs2;
}

// Consumer synchronization for dispatcher, ps2 cs2
void elevator::GetElevatorStatus_dispatcher(thedata *data){
    CSemaphore      completed("done", 0, 1);

	// Producer lock to consume
	ps2->Wait();		
	if (completed.Read() > 0)
		return;
	// Data lock
	theMutex->Wait();
	if (completed.Read() > 0)
		return;
	// Read all data from elevator
	data->dest_floor 	= datapool_ptr -> dest_floor;
	data->curr_floor 	= datapool_ptr -> curr_floor;
	data->closed 		= datapool_ptr -> closed;
	data->idle 			= datapool_ptr -> idle;
	data->up 			= datapool_ptr -> up;
	data->fault			= datapool_ptr -> fault;
	// Data unlock
	theMutex->Signal();
	// Consumer unlock
	cs2->Signal();	
	Sleep(100);
}

// Consumer synchronization for io, ps1 cs1
void elevator::GetElevatorStatus_io(thedata *data){
    CSemaphore      completed("done", 0, 1);

	// Producer lock to consume
	ps1->Wait();
	if (completed.Read() > 0)
		return;
	// Data lock
	theMutex->Wait();
	if (completed.Read() > 0)
		return;
	// Read all data from elevator
	data->dest_floor 	= datapool_ptr -> dest_floor;
	data->curr_floor 	= datapool_ptr -> curr_floor;
	data->closed 		= datapool_ptr -> closed;
	data->idle 			= datapool_ptr -> idle;
	data->up 			= datapool_ptr -> up;
	data->fault			= datapool_ptr -> fault;
	
	// Data unlock
	theMutex->Signal();
	// Consumer unlock
	cs1->Signal();	
Sleep(100);
}

// Producer consumer semaphore.
// Waits for both io and dispatcher to finish reading, then locks data, then writes to it
// Then signals to them the OK to read
// Does not write until it knows dispatcher and io has read the last instance of write.
void elevator::Update_Status(thedata *data){
	CSemaphore completed("done", 0, 1);

	if (completed.Read() > 0 ){
		return;
	}
	// Elevator is the producer, we produce the floors. IO and dispatcher reads the current value
	
	cs1->Wait();		
	if (completed.Read()  > 0){
		return;
	}
	cs2->Wait();
	if (completed.Read()  > 0){
		return;
	}
	theMutex->Wait();

	datapool_ptr->curr_floor 	= data->curr_floor;
	datapool_ptr->dest_floor 	= data->dest_floor;
	datapool_ptr->idle 			= data->idle;
	datapool_ptr->closed 		= data->closed;
	datapool_ptr->up 			= data->up;
	datapool_ptr->fault			= data->fault;

	theMutex->Signal();
			
	ps1->Signal();		// signal the consumer semaphore to wake up the producer
	ps2->Signal();
	Sleep(100);
}

// Unneeded.
// void elevator::GetElevatorStatus(thedata &data){

// 	theMutex->Wait();

// 	data.curr_floor		= datapool_ptr->curr_floor;
// 	data.dest_floor 	= datapool_ptr->dest_floor;
// 	data.idle 			= datapool_ptr->idle;
// 	data.closed 		= datapool_ptr->closed;
// 	data.up 			= datapool_ptr->up;
// 	data.fault			= datapool_

// 	theMutex->Signal();
// }

/*
create vector leave dest as it was
dest still 

decode encode vector<int>

*/
//ENCODE AND DECODE MESSAGES FROM MAILBOX
UINT encode(int curr, int dest, bool idle, bool closed, bool up, bool fault){ 
	int returnthing = 0;
	// for (int i = 0; i < 3; ++i){
	// 	dest.push_back(6);
	// }

	returnthing += dest ;
	cout << " dest: " << dest;
	returnthing += (curr * 10);
	// cout << " cur: " << curr;
	returnthing += idle ? 100 : 0;
	returnthing += closed ? 1000 : 0;
	returnthing += up ? 10000 : 0;
	returnthing += fault ? 5000 : 0;
	// cout << "FAULT " <<fault;
	// for (int i = 0; i < dest.size(); i++){
	// 	returnthing += (UINT) dest[i] * 10000 * pow(10, i);
	// }

	return returnthing;	
}

thedata decode(UINT message){
	thedata decoded;
	decoded.dest_floor  = ((message)/ 1)% 10;
	decoded.curr_floor 	= ((message) / 10) % 10;
	decoded.idle 		= ((message) / 100) % 10;
	decoded.up 		= ((message) / 10000) % 10;
	
// Decode fault is 5
	int temp			= ((message) / 1000) % 10;
	decoded.up 			= (temp == 6 || temp == 1);
	decoded.fault 		= (temp > 1);
	// cout << "decode fault: " << decoded.fault;
	return decoded;
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

// void elevator::WriteToConsole(int x, int y){
// 	theMutex->Wait();
// 	int dest_floor = datapool_ptr->dest_floor;
// 	int curr_floor = datapool_ptr->curr_floor;
// 	bool closed = datapool_ptr->closed;
// 	bool idle = datapool_ptr->idle;
// 	bool up = datapool_ptr->up;
// 	theMutex->Signal();
// 	WriteToScreen(x, y, "Dest floor: " + to_string(datapool_ptr->dest_floor));
// 	WriteToScreen(x, y+1, "Curr floor: " + to_string(datapool_ptr->curr_floor));
// 	if (closed)
// 		WriteToScreen(x, y+2, "Door closed");
// 	else
// 		WriteToScreen(x, y+2, "Door open  ");
// 	if (idle)
// 		WriteToScreen(x, y+3, "Idle    ");
// 	else
// 		WriteToScreen(x, y+3, "Not idle");
// 	if (up)
// 		WriteToScreen(x, y+4, "Going up  " );
// 	else
// 		WriteToScreen(x, y+4, "Going down" );

// }

// // Not even needed.... or is it?
// void elevator::WriteToScreen(int x, int y, string input) {
// 	console.Wait();
// 	MOVE_CURSOR(x, y);             	// move cursor to cords [x,y] 
// 	// cout << input << " @ " << x << " " << y;
// 	cout << input ;
// 	//printf("%s @ ( %d , %d )", input, x, y);
// 	cout.flush();
// 	//fflush(stdout);		      	// force output to be written to screen now
// 	// Move back to where input is
// 	//MOVE_CURSOR(18,5);
// 	console.Signal();
// }


// Unused
// void elevator::set_dest(int floor){
// 	if (datapool_ptr->idle){
// 		datapool_ptr->dest_floor = floor;
// 	}
// 	console.Wait();
// 	MOVE_CURSOR(0,1);
// 	cout << "dest floor "<< datapool_ptr->dest_floor;
// 	cout << " idle is " << datapool_ptr->idle;
// 	console.Signal();
// }


