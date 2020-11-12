	// main.cpp: defines the entry point for the console application
#include "rt.h"
#include "Q8Parent/elevator.h"
#include <thread>
#include <iostream>
#include <regex>
#include <vector>
#include <algorithm>
using namespace std;

struct io_dispatcher_pipeline {
	char first;
	char second;
};

void e1(thedata *elevator1data);
void e2(thedata *elevator2data);
void algo(thedata *elevator1data, thedata *elevator2data, CProcess *elevator1_process, CProcess *elevator2_process);

CRendezvous r1("Rendezvous",4);

elevator elev1("ee1");
elevator elev2("ee2");

/* This is the MAIN dispatcher process. It creates other processes and threads. 
- Creates elevator1 process, elevator2 process, io process.
- Creates e1, e2, algo thread
*/
int main(void) {

	

	// Create 3 processes
	CProcess elevator1_process("elevator1.exe", NORMAL_PRIORITY_CLASS, PARENT_WINDOW, ACTIVE);
	CProcess elevator2_process("elevator2.exe", NORMAL_PRIORITY_CLASS, PARENT_WINDOW, ACTIVE);
	CProcess io_process("io.exe", NORMAL_PRIORITY_CLASS, PARENT_WINDOW, ACTIVE);
	r1.Wait();
	
	thedata elevator1data;
	thedata elevator2data;
// Sleep(1000);
// 	while (1){
		
// 		console.Wait();
// 		MOVE_CURSOR(0,8);
//  		cout << "Enter a UINT: ";
//  		cin >> a;
// 		console.Signal();
// 		elevator1_process.Post(a);
		
// 	}
	// Create 3 threads
	thread t1(e1, &elevator1data); 
	thread t2(e2, &elevator2data);
	thread t3(algo, &elevator1data, &elevator2data, &elevator1_process, &elevator2_process);



	// Wait for threads to finish
	t1.join();
	t2.join();
	t3.join();
	
	// Waiting for processes to terminate
	elevator1_process.WaitForProcess();
	elevator2_process.WaitForProcess();
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
		// if (completion.Read() == 1)
			// return;
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
		/* insert algo here
		1. check pipeline for stuff
		2. if there is stuff, and its not ee, decide which elevator will pass to
		- if ee, go to ground, open, stop


		CHECKS: 

		1. idle check
		-BOTH ELEVATORS IDLE
			Get the closest one to the command floor
			Same floor, command elevator 1
			
			Checks:
			1. not same curr floor, if false- send e1
			2. Closest floor (curr floor vs floor to dispatch to)

		-ONE ELEVATOR IDLE
			if passenger direction == elevator direction, stop otw, EVEN if one elevator is idle (POWER SAVINGS), sort low to high
			Otherwise use idle elevator

			Checks:
			1. If command direction == non-idle elevator direction && non-idle elevator curr floor < idle elevator curr floor
		-NONE IDLE
			Delegate to closest dest with same direction, sort low to high 
			Otherwise use first to be idle.

			Checks:
			1. if elevator in same direction and before/after dispatch floor, already moving changes dest to this floor and then sets dest again
			2. if none in same direction, checks for closest to be finihsing, and puts it into that one, then sorts (vector sort)

		1
		0
		2->9   
		7->9   1 0

		Overide:
		-FAULT
			Stop elevator. have graphic, clear dest vector
		-END
			Stop both elevators, go to ground, open, stop
	
		
Pipeline io pushes to queue
Dispatcher algo pops queue depending on idle elevators and checks above.


		*/
		if (regex_search(s, inside)){// - Inside: 1 or 2, 0-9 {[1-2][0-9]}
			// Elevator 1
			if (temp.first == '1'){
				console.Wait();
				MOVE_CURSOR(0,2);
				cout << "setting dest floor "<< temp.second;
				// cout << elevator1data->curr_floor << " " << false << true <<(((int)temp.second - elevator1data->curr_floor)>0? true: false) ;
				// cout << " " << encode(elevator1data->curr_floor, (int)temp.second, false, true, (((int)temp.second - elevator1data->curr_floor)>0? true: false));
				console.Signal();
				int asfd = temp.second - '0';
				elevator1_process->Post(encode(elevator1data->curr_floor, asfd, false, true, ((asfd - elevator1data->curr_floor)>0? true: false), elevator1data->fault));
				//elevator1_process->Post(temp.second);
				// e1_command.Signal();
			}
			// Elevator 2, do nohting for now
			else if (temp.first == '2'){
				// elev2.set_dest(temp.second);
				int asfd = temp.second - '0';
				elevator2_process->Post(encode(elevator2data->curr_floor, asfd, false, true, ((asfd - elevator2data->curr_floor)>0? true: false), elevator2data->fault));
			
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
			if (temp.second == '1'){
				if (temp.first == '-'){
					// Stop elevator 1 and clear destinations.
					elevator1_process->Post(encode(elevator1data->curr_floor, elevator1data->dest_floor, elevator1data->idle, elevator1data->closed, elevator1data->up, true));
				}
				if (temp.first == '+'){
					// Stop elevator 1 and clear destinations.
					elevator1_process->Post(encode(elevator1data->curr_floor, elevator1data->curr_floor, elevator1data->idle, elevator1data->closed, elevator1data->up, false));
				}
			}
			else if (temp.second == '2'){
				if (temp.first == '-'){
					// Stop elevator 2 and clear destinations.
					elevator2_process->Post(encode(elevator2data->curr_floor, elevator2data->dest_floor, elevator2data->idle, elevator2data->closed, elevator2data->up, true));
				}
				if (temp.first == '+'){
					// Stop elevator 2 and clear destinations.
					elevator2_process->Post(encode(elevator2data->curr_floor, elevator2data->curr_floor, elevator2data->idle, elevator2data->closed, elevator2data->up, false));
				}
			}
			
		}
		else if (regex_search(s, end)){
			//pause
		}
		
		// e1_command.Signal() or e2_command.Signal(); 
		// puts info into elevator

		//elev1.Update_Status(&data);
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