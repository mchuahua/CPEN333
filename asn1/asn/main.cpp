// main.cpp: defines the entry point for the console application
#include "rt.h"
#include "elevator.h"
#include <thread>
#include <iostream>
using namespace std;

struct io_dispatcher_pipeline {
	char first;
	char second;
};


void e1();
void e2();
void algo();

// This is the dispatcher process. It creates other processes and delegates things.
int main(void) {
	
	// Create 3 processes
	CProcess elevator1_process("elevator1.exe", NORMAL_PRIORITY_CLASS, PARENT_WINDOW, ACTIVE);
	CProcess elevator2_process("elevator2.exe", NORMAL_PRIORITY_CLASS, PARENT_WINDOW, ACTIVE);
	CProcess io_process("io.exe", NORMAL_PRIORITY_CLASS, PARENT_WINDOW, ACTIVE);
	
	// Create 3 threads
	thread t1(e1); 
	thread t2(e2);
	thread t3(algo);

	// Wait for threads to finish
	t1.join();
	t2.join();
	t3.join();
	
	// Waiting for processes to terminate
	elevator1_process.WaitForProcess();
	elevator1_process.WaitForProcess();
	io_process.WaitForProcess();


	// Prevent auto exit
	getchar();
	return 0;
}
// Responds to changes in elevator1 status, and copies this status to local variables so that when a new command arrives, it can be dealt with immediately
void e1(){
	CSemaphore completion("done", 0, 1);
	elevator e1("hehe xd");

	while(completion.Read() != 1){
		
	}

}

// Responds to changes in elevator2 status, and copies this status to local variables so that when a new command arrives, it can be dealt with immediately 
void e2(){
	CSemaphore completion("done", 0, 1);
	elevator e2("hehe xd");
	while(completion.Read() != 1){

	}

}

// Checks pipeline for stuff. Triggers completion or
// looks at status of elevators and decides which elevator is in the best position to deal with incoming up/down request
void algo(){
	CTypedPipe <io_dispatcher_pipeline> pipe1("io_dispatcher_pipeline", 1024);
	CSemaphore completion("done", 0, 1);
    CSemaphore e1_command("e1", 0, 1);
    CSemaphore e2_command("e2", 0, 1);

	io_dispatcher_pipeline temp;
	
	// Forever loop
	while (temp.first != 'e' && temp.second != 'e'){

		// insert algo here


		// e1_command.Signal() or e2_command.Signal(); 
		// puts info into mailbox (? wtf is this?)

		pipe1.Read(&temp);
	}

	completion.Signal();
}