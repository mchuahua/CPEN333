#include "../rt.h"
#include "../elevator.h"
#include <iostream>

using namespace std;

int main()
{
	cout << "Hello from elevator1 process !!!!!!" << endl;
	CSemaphore completion("done", 0, 1);
	CSemaphore command("e1", 0, 1);

	elevator e1("hehe xd");

	while(completion.Read() != 1){
		command.Wait();
		// Read from mailbox (? wtf is this?)
		// updates named monitor elevator1
	}

	return 0;
}

