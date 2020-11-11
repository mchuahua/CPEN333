#include "../rt.h"
#include "../elevator.h"
#include <iostream>
#include <thread>
using namespace std;

struct io_dispatcher_pipeline {
	char first;
	char second;
};

struct data {
	int dest_floor;
	int curr_floor
	bool openclosed;
};

void e1();
void e2();
void input();

int main()
{
	cout << "Hello from io process !!!!!!" << endl;

	// Creating three threads: updates from elevator1 / 2 + screen redraw, input of commands
	thread t1(e1);
	// thread t2(e2);
	thread t3(input);

	// Wait for threads to finish.
	t1.join();
	// t2.join();
	t3.join();
	return 0;
}

// Handles updates from elevator 1 + redraws screen using move_cursor + mutex
// Attempts to get status of elevator. may be blocked if no new data
void e1(){
	CSemaphore completion("done", 0, 1);
	
	CSemaphore		ps1("PS1", 0, 1);    // semaphore with initial value 0 and max value 1
	CSemaphore		cs1("CS1", 1, 1);    // semaphore with initial value 1 and max value 1

	// CMutex console("console");    
	CMutex console("console");


	while(completion.Read() != 1){
		
	}	


}

// Handles updates from elevator 2 + redraws screen using move_cursor + mutex
// Attempts to get status of elevator. may be blocked if no new data
void e2(){
	CSemaphore completion("done", 0, 1);
	// CMutex console("console");
	elevator e2("hehe xd");
	CSemaphore		ps3("PS3", 0, 1);    // semaphore with initial value 0 and max value 1
	CSemaphore		cs3("CS3", 1, 1);    // semaphore with initial value 1 and max value 1

	while(completion.Read() != 1){
		// get mutex, use e2.WriteToConsole();
	}

}

// Handles input using getch() or getche() ?
void input(){
	CSemaphore completion("done", 0, 1);
	CTypedPipe <io_dispatcher_pipeline> pipe1("io_dispatcher_pipeline", 1024);
	io_dispatcher_pipeline temp;
	// Forever loop
	while(completion.Read() != 1){
		// Get characters

		// Validation of characters (regex)

		// Write to pipeline 
		// temp.first =
		// temp.second = 
		pipe1.Write(&temp);
	}

}

