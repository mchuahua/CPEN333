#include "../rt.h"
#include "../Q8Parent/elevator.h"
#include <iostream>
#include <thread>
#include <regex>
#include <string>

using namespace std;

struct io_dispatcher_pipeline {
	char first;
	char second;
};

CRendezvous r1("Rendezvous",4);

void e1display();
void e2display();
void input();
void setscene();
void anielevator(int elev,int curr_floor, bool closed, bool fault,int prev);

/*
Deals with all things displayed on console.
Gets user input and sends it through pipeline to Dispatcher
Get_elevator_status to show current status and animations

*/


int main()
{
	r1.Wait();
	// cout << "Hello from io process !!!!!!" << endl;
	setscene();
	thedata elevator1data;
	thedata elevator2data;
	// Creating three threads: updates from elevator1 / 2 + screen redraw, input of commands
	thread t1(e1display);
	thread t2(e2display);
	thread t3(input);

	// Wait for threads to finish.
	t1.join();
	t2.join();
	t3.join();
	console.Wait();
	MOVE_CURSOR(0,11);
	cout << "io process ended ";
	MOVE_CURSOR(18,5);
	console.Signal();
	return 0;
}

// Handles updates from elevator 1 + redraws screen using move_cursor + mutex
// Attempts to get status of elevator. may be blocked if no new data
void e1display(){
	CSemaphore completion("done", 0, 1);

	elevator elev1("ee1");
	thedata data;
	console.Wait();
	MOVE_CURSOR(50, 0);
	cout << "ELEVATOR 1 STATUS";
	MOVE_CURSOR(50, 13);
	cout << "ELEVATOR 2 STATUS";
	console.Signal();
	int prev = 0;

	while(completion.Read() != 1){
		elev1.GetElevatorStatus_io(&data);
		console.Wait();
		MOVE_CURSOR(50, 2);             	// move cursor to cords [x,y] 
		cout << "Current floor: " << data.curr_floor;
		MOVE_CURSOR(50, 3);             	// move cursor to cords [x,y] 
		cout << "Dest floor: " << data.dest_floor;
		MOVE_CURSOR(50, 4);             	// move cursor to cords [x,y] 
		if (!data.idle)
			cout << "Idle    ";
		else
			cout << "Not idle";
		MOVE_CURSOR(50, 5);             	// move cursor to cords [x,y] 
		if (data.closed)
			cout << "Doors Closed";
		else
			cout << "Doors Open  ";
		MOVE_CURSOR(50, 6);             	// move cursor to cords [x,y] 
		if (data.up)
			cout << "Going up  ";
		else 
			cout << "Going down";
		MOVE_CURSOR(50, 7);             	// move cursor to cords [x,y] 
		if (data.fault)
			for (int i =2; i < 8; i++){
				MOVE_CURSOR(50, i);
				cout << "FAULT            ";
			}
		else 
			cout << "no fault";
		cout.flush();
		//fflush(stdout);		      	// force output to be written to screen now
		// Move back to where input is
		anielevator (1,data.curr_floor,data.closed,data.fault, prev);
		//MOVE_CURSOR(18,5);
		console.Signal();
		prev = data.curr_floor;
	Sleep(100);
	}

}

// Handles updates from elevator 2 + redraws screen using move_cursor + mutex
// Attempts to get status of elevator. may be blocked if no new data
void e2display(){
	CSemaphore completion("done", 0, 1);
	int prev = 0;

	elevator elev1("ee2");
	thedata data;

	while(completion.Read() != 1){
		elev1.GetElevatorStatus_io(&data);
		console.Wait();
		MOVE_CURSOR(50, 15);             	// move cursor to cords [x,y] 
		cout << "Current floor: " << data.curr_floor;
		MOVE_CURSOR(50, 16);             	// move cursor to cords [x,y] 
		cout << "Dest floor: " << data.dest_floor;
		MOVE_CURSOR(50, 17);             	// move cursor to cords [x,y] 
		if (!data.idle)
			cout << "Idle    ";
		else
			cout << "Not idle";
		MOVE_CURSOR(50, 18);             	// move cursor to cords [x,y] 
		if (data.closed)
			cout << "Doors Closed";
		else
			cout << "Doors Open  ";
		MOVE_CURSOR(50, 19);             	// move cursor to cords [x,y] 
		if (data.up)
			cout << "Going up  ";
		else 
			cout << "Going down";
		MOVE_CURSOR(50, 20);             	// move cursor to cords [x,y] 
		if (data.fault)
			for (int i = 15; i < 21; i++){
				MOVE_CURSOR(50, i);
				cout << "FAULT            ";
			}
		else 
			cout << "no fault";
		cout.flush();
		//fflush(stdout);		      	// force output to be written to screen now
		// Move back to where input is
		anielevator (2,data.curr_floor,data.closed,data.fault, prev);
		//MOVE_CURSOR(18,5);
		console.Signal();
		prev = data.curr_floor;
	Sleep(100);
	}

}

// Handles input using getch()
// Cool regex magic
// Pipelines validated io commands to dispatcher
void input(){
	CSemaphore completion("done", 0, 1);
	CTypedPipe <io_dispatcher_pipeline> pipe1("io_dispatcher_pipeline", 1024);
	io_dispatcher_pipeline temp;
	regex inside("[1-2][0-9]");
	regex outside("[u|d][0-9]");
	regex fault("[+|-][1|2]");
	regex end("[e]{2}");

	// Forever loop
	while(1){
		// Get characters
		// TODO: add mutex
		console.Wait();
		MOVE_CURSOR(0,5);
		cout << "Enter characters: ";
		console.Signal();
		if (completion.Read() == 1)
			return;
		char fist = _getch();
		if (completion.Read() == 1)
			return;
		char secd = _getch();
		if (completion.Read() == 1)
			return;
		string s({fist, secd});

		// console.Wait();
		// cout << s;
		// console.Signal();

		// Validation of characters (regex)
		// Regex for : 
		// - Inside: 1 or 2, 0-9 {[1-2][0-9]}
		// - outisde u or d, 0-9 {[u|d][0-9]}
		// - fault + or -, 1 or 2 {[+|-][1|2]}
		// - end e e {[e]{2}}
				// completion.Signal()

		// Should never reach this
		if (s.size() != 2){
		 	continue;
		}
		else if (regex_search(s, inside)){
			console.Wait();
			MOVE_CURSOR(0,6);
			cout << "matched inside                           ";
			console.Signal();
		}
		else if (regex_search(s, outside)){
			console.Wait();
			MOVE_CURSOR(0,6);
			cout << "matched outside                           ";
			console.Signal();
		}
		else if (regex_search(s, fault)){
			console.Wait();
			MOVE_CURSOR(0,6);
			cout << "Matched fault                             ";
			console.Signal();
		}
		else if (regex_search(s, end)){
			console.Wait();
			MOVE_CURSOR(0,6);
			cout << "matched end                               ";
			console.Signal();
			// completion.Signal();
			temp.first = fist;
			temp.second = secd;
			pipe1.Write(&temp);
			return;
		}
		else{
			console.Wait();
			MOVE_CURSOR(0,6);
			cout << "Incorrect instruction. Please try again.";
			console.Signal();
			continue;
		}
		
		// Write to pipeline 
		temp.first = fist;
		temp.second = secd;
		pipe1.Write(&temp);
	}

}
void setscene() {
	console.Wait();
	MOVE_CURSOR(0, 0);
												cout << R"(	     
										     _________|_________     || 
										    /                   \   _||_
										   <                     > ( oo )
										   <      Freefall       >_| ^^ |_
										   <      Elevators      >   @    \
										  /~                     ~\ . . _ |
										 /~~                     ~~\    | |
										/~~~~~~~~~~~~~~~~~~~~~~~~~~~\/ _| |
										|[            |            ]|/ / [m]
										|[            |            [m]
										|[            |            ]|
										|[            |            ]|
										|[============|============]|
										|[            |            ]|
										|[            |            ]|
										|[            |            ]|
										|[            |            ]|
										|[============|============]|
										|[            |            ]|
										|[            |            ]|
										|[            |            ]|
										|[            |            ]|
										|[============|============]|
										|[            |            ]|
										|[            |            ]|
										|[            |            ]|
										|[            |            ]|
										|[============|============]|
										|[            |            ]|
										|[            |            ]|
										|[            |            ]|
										|[            |            ]|
										|[============|============]|
										|[            |            ]|
										|[            |            ]|
										|[            |            ]|
										|[            |            ]|
										|[============|============]|
										|[            |            ]|
										|[            |            ]|
										|[            |            ]|
										|[            |            ]|
										|[============|============]|
										|[            |            ]|
										|[            |            ]|
										|[            |            ]|
										|[            |            ]|
										|[============|============]|
										|[            |            ]|
										|[            |            ]|
										|[            |            ]|
										|[            |            ]|
										|[============|============]|
										|[            |            ]|
										|[            |            ]|
										|[            |            ]|
										|[            |            ]|
										|[============|============]|)";
	// TODO: make bottom bulbous
	console.Signal();
	return;
}

void anielevator(int elev,int curr_floor, bool closed, bool fault, int prev){
	int topleftx = 84+((elev-1 )*13);
	int toplefty = 54-(5*curr_floor);
	int toplefty_prev = 54 - (5 * prev);
	console.Wait();

	MOVE_CURSOR(topleftx, toplefty_prev);
	cout <<"         ";
	MOVE_CURSOR(topleftx,toplefty_prev+1);
	cout <<"         ";
	MOVE_CURSOR(topleftx,toplefty_prev+2);
	cout <<"         ";
   	MOVE_CURSOR(topleftx,toplefty_prev+3);
	cout <<"         ";
	
	if (closed){
		MOVE_CURSOR(topleftx,toplefty);
		cout <<"--------";
		MOVE_CURSOR(topleftx,toplefty+1);
		cout <<"|  ||  |";
		MOVE_CURSOR(topleftx,toplefty+2);
		cout <<"|  ||  |";
   		MOVE_CURSOR(topleftx,toplefty+3);
	    cout <<"--------";
	}
	else if (!closed){
		MOVE_CURSOR(topleftx,toplefty);
		cout <<"--------";
		MOVE_CURSOR(topleftx,toplefty+1);
		cout <<"||    ||";
		MOVE_CURSOR(topleftx,toplefty+2);
		cout <<"||    ||";
   		MOVE_CURSOR(topleftx,toplefty+3);
	    cout <<"--------";
	}
	if(fault) {
		MOVE_CURSOR(topleftx,toplefty);
		cout <<"--------";
		MOVE_CURSOR(topleftx,toplefty+1);
		cout <<"|  \\/  |";
		MOVE_CURSOR(topleftx,toplefty+2);
		cout <<"|  /\\  |";
   		MOVE_CURSOR(topleftx,toplefty+3);
	    cout <<"--------";
	}
	
	console.Signal();
	return;
}
