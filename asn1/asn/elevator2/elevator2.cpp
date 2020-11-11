#include "../rt.h"
#include "../elevator.h"
#include <iostream>

using namespace std;

int main()
{
	cout << "Hello from elevator2 process !!!!!!" << endl;
	CSemaphore completion("done", 0, 1);
	CSemaphore command("e2", 0, 1);

	elevator e2("ee2");

	// while(completion.Read() != 1){
	// 	command.Wait();
	// 	// Read from mailbox (? wtf is this?)
	// 	// updates named monitor elevator2
	// }

	return 0;
}

