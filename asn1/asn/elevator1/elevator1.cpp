#include "../rt.h"
#include "../Q8Parent/elevator.h"
#include <iostream>

using namespace std;

void test();

int main()
{
	cout << "Hello from elevator1 process !!!!!!" << endl;
	CSemaphore completion("done", 0, 1);
	CSemaphore command("e1", 0, 1);

	elevator e1("ee1");

	while(completion.Read() != 1){
		// Dispatcher signals command available from dispatcher
		command.Wait();
		// Updates status 
		e1.GetElevatorStatus();

		// updates named monitor elevator1
	}

	return 0;
}