#include "../rt.h"
#include "../Q8Parent/elevator.h"
#include <iostream>

using namespace std;

/* Elevator 2:
- Have wait semaphore triggered by dispatcher
- Have mailbox to get status from dispatcher
- Update status using Update_Status()
*/
int main()
{
cout << "Hello from elevator2 process !!!!!!" << endl;
	CSemaphore completion("done", 0, 1);

	elevator e1("ee2");

	CMailbox mailbox;
	UINT message = 0;
	thedata decoded;
	//vector<int> destinations;
	//currDigit = (absolute(message) / 10^index) % 10;
	// Dispatcher signals command available from dispatcher
	do {
		if (mailbox.TestForMessage()) {
			// Updates status 
			message = mailbox.GetMessage();
			char messages[] = {message};
			int asf = atoi(messages);
			console.Wait();
			MOVE_CURSOR(0, 4);
			printf("%u", message);
			console.Signal();
			decoded = decode(message);
		}
		else{
			Sleep(750);
			if (completion.Read() == 1)
				return 0;
			if ((decoded.dest_floor - decoded.curr_floor)> 0){
				decoded.idle = true;
				decoded.curr_floor++;
			}
			else if ((decoded.dest_floor - decoded.curr_floor) < 0){
				decoded.idle = true;
				decoded.curr_floor--;
			}
			else
			{
				decoded.idle = false;
			}
			
		}
		e1.Update_Status(&decoded);
		// updates named monitor elevator1
	} while (completion.Read() != 1);

	return 0;
}

