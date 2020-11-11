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

void e1display();
void e2display();
void input();

int main()
{
	cout << "Hello from io process !!!!!!" << endl;

	thedata elevator1data;
	thedata elevator2data;
	// Creating three threads: updates from elevator1 / 2 + screen redraw, input of commands
	// thread t1(e1display);
	// thread t2(e2display);
	thread t3(input);

	// Wait for threads to finish.
	// t1.join();
	// t2.join();
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

	while(completion.Read() != 1){
		//elev1.WriteToConsole(50, 50);
	}

}

// Handles updates from elevator 2 + redraws screen using move_cursor + mutex
// Attempts to get status of elevator. may be blocked if no new data
void e2display(){
	CSemaphore completion("done", 0, 1);

	elevator elev1("ee2");

	while(completion.Read() != 1){
		elev1.WriteToConsole(50, 50);
	}

}

// Handles input using getch() or getche() ?
void input(){
	CSemaphore completion("done", 0, 1);
	CTypedPipe <io_dispatcher_pipeline> pipe1("io_dispatcher_pipeline", 1024);
	io_dispatcher_pipeline temp;
	regex inside("[1-2][0-9]");
	regex outside("[u|d][0-9]");
	regex fault("[+|-][1|2]");
	regex end("[e]{2}");
	smatch m;

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

		console.Wait();
		cout << s;
		console.Signal();

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

