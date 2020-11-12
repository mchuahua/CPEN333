// main.cpp: defines the entry point for the console application
#include "rt.h"
#include "Q8Parent/elevator.h"
#include <thread>
#include <iostream>
#include <regex>
using namespace std;

struct io_dispatcher_pipeline {
	char first;
	char second;
};

void e1(thedata *elevator1data);
void e2(thedata *elevator2data);
void algo(thedata *elevator1data, thedata *elevator2data, CProcess *elevator1_process, CProcess *elevator2_process);

CRendezvous r1("Rendezvous",2);

elevator elev1("ee1");
elevator elev2("ee2");

/* This is the MAIN dispatcher process. It creates other processes and threads. 
- Creates elevator1 process, elevator2 process, io process.
- Creates e1, e2, algo thread
*/
int main(void) {
	console.Wait();
		cout << encode(4,9, true, true, true);
		console.Signal();

	decode(encode(4, 9, true, true, true));
	// Create 3 processes
	CProcess elevator1_process("elevator1.exe", NORMAL_PRIORITY_CLASS, PARENT_WINDOW, ACTIVE);
	CProcess elevator2_process("elevator2.exe", NORMAL_PRIORITY_CLASS, PARENT_WINDOW, ACTIVE);
	CProcess io_process("io.exe", NORMAL_PRIORITY_CLASS, PARENT_WINDOW, ACTIVE);
	r1.Wait();
	
	thedata elevator1data;
	thedata elevator2data;


	// Create 3 threads
	thread t1(e1, &elevator1data); 
	//thread t2(e2, &elevator2data);
	thread t3(algo, &elevator1data, &elevator2data, &elevator1_process, &elevator2_process);



	// Wait for threads to finish
	t1.join();
	//t2.join();
	t3.join();
	
	// Waiting for processes to terminate
	// elevator1_process.WaitForProcess();
	//elevator1_process.WaitForProcess();
	io_process.WaitForProcess();
	console.Wait();
	MOVE_CURSOR(0,12);
	cout << "dispatcher (main) process ended. Press enter to end program";
	MOVE_CURSOR(18,5);
	console.Signal();
	// Prevent auto exit
	getchar();
	return 0;
}

// Get elevator 1 status and puts it into local elevator 1 object
void e1(thedata *elevator1data){
	CSemaphore completion("done", 0, 1);

	while(completion.Read() != 1){
		elev1.GetElevatorStatus_dispatcher(elevator1data);
	}
}

// Get elevator 1 status and puts it into local elevator 1 object
void e2(thedata *elevator2data){
	CSemaphore completion("done", 0, 1);
	
	while(completion.Read() != 1){
		elev2.GetElevatorStatus_dispatcher(elevator2data);
	}
}

/* Checks pipeline for IO commands.
Does stuff depending on the command: inside, outside, fault, exit 
	-Decides what elevator the command will be given to.
	-Uses mailbox to delegate where elevator will go to.
	-Signals elevator1/2 process to update the elevator1/2 status
 looks at status of elevators and decides which elevator is in the best position to deal with incoming up/down request
 */
void algo(thedata *elevator1data, thedata *elevator2data, CProcess *elevator1_process, CProcess *elevator2_process){
	CTypedPipe <io_dispatcher_pipeline> pipe1("io_dispatcher_pipeline", 1024);
	CSemaphore completion("done", 0, 1);
    CSemaphore e1_command("e1", 0, 1);
    CSemaphore e2_command("e2", 0, 1);
	regex inside("[1-2][0-9]");
	regex outside("[u|d][0-9]");
	regex fault("[+|-][1|2]");
	regex end("[e]{2}");
	io_dispatcher_pipeline temp;
	temp.first = ' ';
	temp.second = ' ';
	// bool e1_outside = true;
	// bool e2_outside = true;

	thedata data;

	// Forever loop
	while (temp.first != 'e' && temp.second != 'e'){
		pipe1.Read(&temp);
		console.Wait();
		MOVE_CURSOR(0,8);
		cout << "Read " << temp.first << temp.second;
		MOVE_CURSOR(18,5);
		console.Signal();
		string s({temp.first, temp.second});
		// insert algo here
		// 1. check pipeline for stuff
		// 2. if there is stuff, and its not ee, decide which elevator will pass to
		// - if ee, go to ground, open, stop
		// - if both elevators are not idle, wait until the first one is idle and pass it to that one.
		// if both elevators are idle, get the closest one to the command floor
		if (regex_search(s, inside)){// - Inside: 1 or 2, 0-9 {[1-2][0-9]}
			// Elevator 1
			if (temp.first == '1'){
				console.Wait();
				MOVE_CURSOR(0,2);
				cout << "setting dest floor "<< temp.second;
				console.Signal();
				elevator1_process->Post(1);
				e1_command.Signal();
			}
			// Elevator 2, do nohting for now
			else if (temp.first == '2'){
				// elev2.set_dest(temp.second);
			}
		}
		else if (regex_search(s, outside)){// - outisde u or d, 0-9 {[u|d][0-9]}
			// MEAT OF THE ALGORITHM
			//send elev to floor
			// Elevator 1
			if (temp.first == '1'){
				
			}
			// Elevator 2, do nohting for now
			else if (temp.first == '2'){
				// elev2.set_dest(temp.second);
			}
			
		}
		else if (regex_search(s, fault)){// - fault + or -, 1 or 2 {[+|-][1|2]}
			//pause
		}
		else if (regex_search(s, end)){
			//pause
		}
		
		// e1_command.Signal() or e2_command.Signal(); 
		// puts info into elevator

		elev1.Update_Status(&data);
		// elev2.Update_Status(data);
	}
	console.Wait();
	MOVE_CURSOR(0,10);
	cout << "out of ee exit ";
	MOVE_CURSOR(18,5);
	console.Signal();

	completion.Signal();
	return;
}