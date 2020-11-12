#include "../rt.h"
#include "../Q8Parent/elevator.h"
#include <iostream>

using namespace std;

/* Elevator 1:
- Have wait semaphore triggered by dispatcher
- Have mailbox to get status from dispatcher
- Update status using Update_Status()
*/
int main()
{
	cout << "Hello from elevator1 process !!!!!!" << endl;
	CSemaphore completion("done", 0, 1);
	CSemaphore command("e1", 0, 1);

	elevator e1("ee1");

	CMailbox mailbox;
	UINT message;
	thedata decoded;
	//currDigit = (absolute(message) / 10^index) % 10;
	while(completion.Read() !=1){
		// Dispatcher signals command available from dispatcher
		command.Wait();
		// Updates status 
		message = mailbox.GetMessage();
		console.Wait();
		cout << message;
		console.Signal();
		decoded.dest_floor = 69;
		e1.Update_Status(&decoded);

		// updates named monitor elevator1
	}
	return 0;
}