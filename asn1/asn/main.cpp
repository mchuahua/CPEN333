// main.cpp: defines the entry point for the console application
#include "rt.h"
#include "Q8Parent/elevator.h"
#include <thread>
#include <iostream>
using namespace std;

struct io_dispatcher_pipeline {
	char first;
	char second;
};

void e1(thedata *elevator1data);
void e2(thedata *elevator2data);
void algo(thedata *elevator1data, thedata *elevator2data);

// This is the dispatcher process. It creates other processes and delegates things.
int main(void) {
	
	// Create 3 processes
	// CProcess elevator1_process("elevator1.exe", NORMAL_PRIORITY_CLASS, PARENT_WINDOW, ACTIVE);
	//CProcess elevator2_process("elevator2.exe", NORMAL_PRIORITY_CLASS, PARENT_WINDOW, ACTIVE);
	CProcess io_process("io.exe", NORMAL_PRIORITY_CLASS, PARENT_WINDOW, ACTIVE);
	
	thedata elevator1data;
	thedata elevator2data;
	// Create 3 threads
	// thread t1(e1, &elevator1data); 
	//thread t2(e2, &elevator2data);
	// thread t3(algo, &elevator1data, &elevator2data);

	// Wait for threads to finish
	// t1.join();
	//t2.join();
	// t3.join();
	
	// Waiting for processes to terminate
	// elevator1_process.WaitForProcess();
	//elevator1_process.WaitForProcess();
	io_process.WaitForProcess();

	// Prevent auto exit
	getchar();
	return 0;
}

// Responds to changes in elevator1 status, and copies this status to local variables so that when a new command arrives, it can be dealt with immediately
void e1(thedata *elevator1data){
	CSemaphore completion("done", 0, 1);

	elevator elev1("ee1");

	while(completion.Read() != 1){
		elev1.dispatcher_syncrhonize(elevator1data);
	}
}

// Responds to changes in elevator2 status, and copies this status to local variables so that when a new command arrives, it can be dealt with immediately 
void e2(thedata *elevator2data){
	CSemaphore completion("done", 0, 1);
	
	elevator elev1("ee2");

	while(completion.Read() != 1){
		elev1.dispatcher_syncrhonize(elevator2data);
	}
}

// Checks pipeline for stuff. Triggers completion or
// looks at status of elevators and decides which elevator is in the best position to deal with incoming up/down request
void algo(thedata *elevator1data, thedata *elevator2data){
	CTypedPipe <io_dispatcher_pipeline> pipe1("io_dispatcher_pipeline", 1024);
	CSemaphore completion("done", 0, 1);
    CSemaphore e1_command("e1", 0, 1);
    CSemaphore e2_command("e2", 0, 1);

	io_dispatcher_pipeline temp;
	temp.first = ' ';
	temp.second = ' ';
	
	// Forever loop
	while (temp.first != 'e' && temp.second != 'e'){
		// insert algo here
		// 1. check pipeline for stuff
		// 2. if there is stuff, and its not ee, decide which elevator will pass to
		// - if ee, go to ground, open, stop
		// - if both elevators are not idle, wait until the first one is idle and pass it to that one.
		// if both elevators are idle, get the closest one to the command floor
		
		// e1_command.Signal() or e2_command.Signal(); 
		// puts info into mailbox (? wtf is this?)

		pipe1.Read(&temp);
	}

	completion.Signal();
}