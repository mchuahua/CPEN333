#include "../rt.h"
#include "../Q8Parent/elevator.h"
#include <iostream>
#include <stdlib.h>
#include <utility>

using namespace std;
CRendezvous r1("Rendezvous",4);


/* Elevator 1:
- Have wait semaphore triggered by dispatcher
- Have mailbox to get status from dispatcher
- Update status using Update_Status()
*/
int main()
{
	r1.Wait();

	// cout << "Hello from elevator1 process !!!!!!" << endl;
	CSemaphore completion("done", 0, 1);
	CSemaphore command("e1", 0, 1);

	elevator e1("ee1");

	CMailbox mailbox;
	UINT message = 0;
	UINT message2 = 0;
	UINT message3 = 0;
	thedata decoded;
	bool old = false;
	//vector<int> destinations;
	//currDigit = (absolute(message) / 10^index) % 10;
	// Dispatcher signals command available from dispatcher
	do {


		// Updates status 
		if (mailbox.TestForMessage()){

			message = mailbox.GetMessage();
			command.Wait();
			message2 = mailbox.GetMessage();
			message3 = mailbox.GetMessage();

			console.Wait();
			MOVE_CURSOR(0, 4);
			printf("%u ", message);
			printf("%u ", message2);
			printf("%u", message3);
			console.Signal();
			decoded = decode(message, message2, message3);
		}
		else if (decoded.fault){
			// Clear all requests
			// cout << "THERE IS FAUAALAULTATLULTAT";
		}
		else{
			Sleep(750);
			
			if (completion.Read() == 1)
				return 0;
			if (old){
				decoded.closed = true;
			}
			// vector<int> destinations;
			vector<pair<int, int>> destinations; // pair( diff, location)
			// if (decoded.dest_floor != 10)
			// 	destinations.push_back(decoded.dest_floor );//- decoded.curr_floor);
			// if (decoded.dest_floor2 != 10)
			// 	destinations.push_back(decoded.dest_floor2 );//- decoded.curr_floor);
			// if (decoded.dest_floor3 != 10)
			// 	destinations.push_back(decoded.dest_floor3 );//- decoded.curr_floor);
			// if (decoded.dest_floor4 != 10)
			// 	destinations.push_back(decoded.dest_floor4 );//- decoded.curr_floor);
			// if (decoded.dest_floor5 != 10)
			// 	destinations.push_back(decoded.dest_floor5 );//- decoded.curr_floor);
			// if (decoded.up){
			// 	int before = 100;
			// 	for (int it = 0 ; it < destinations.size(); ++it){
			// 		if (destinations[it] > decoded.curr_floor && destinations[it] < 10){
			// 			int difference = destinations[it] - decoded.curr_floor;
			// 			if (difference < before){
			// 				decoded.dest_floor = destinations[it];
			// 				destinations[it] = 10;
			// 				// .replace((destinations.begin(),destinations.end(),it,10));
			// 			}
			// 			before = difference;
			// 		}
			// 	}
			// }
			// Get closest UP floors to traverse to

			if (decoded.up && !decoded.idle){
							
				if (decoded.dest_floor != 10)
					destinations.push_back( make_pair(decoded.dest_floor - decoded.curr_floor, 1));
				if (decoded.dest_floor2 != 10)
					destinations.push_back( make_pair(decoded.dest_floor2 - decoded.curr_floor, 2));
				if (decoded.dest_floor3 != 10)
					destinations.push_back( make_pair(decoded.dest_floor3 - decoded.curr_floor, 3));
				if (decoded.dest_floor4 != 10)
					destinations.push_back( make_pair(decoded.dest_floor4 - decoded.curr_floor, 4));
				if (decoded.dest_floor5 != 10)
					destinations.push_back(make_pair(decoded.dest_floor5 - decoded.curr_floor, 5));
				sort(destinations.begin(), destinations.end()); 
				// smallest to biggest difference for first, non negative.
				// First number in array indicates the floor we should stop to first.
				//Find first non-negative
				int non_neg = 0;
				for (int i = 0; i < destinations.size(); ++i){
					if (destinations[i].first > 0){
						non_neg = i;
						break;
					}
				}
				// Swap smallest with dest_floor
				int temp = decoded.dest_floor;
				if (destinations.size() > 0){
					decoded.dest_floor = destinations[non_neg].first;
					if (destinations[non_neg].second == 2)
						decoded.dest_floor2 = temp;
					if (destinations[non_neg].second == 3)
						decoded.dest_floor3 = temp;
					if (destinations[non_neg].second == 4)
						decoded.dest_floor4 = temp;
					if (destinations[non_neg].second == 5)
						decoded.dest_floor5 = temp;
				}
			}
			//vec.erase(std::remove(vec.begin(), vec.end(), 8), vec.end());

			else if (!decoded.up && !decoded.idle) //get closest DOWN floors to traverse to first
			{	//smallets to biggest difference for pair.first, non negative
				if (decoded.dest_floor != 10)
					destinations.push_back( make_pair(decoded.curr_floor - decoded.dest_floor, 1));
				if (decoded.dest_floor2 != 10)
					destinations.push_back( make_pair(decoded.curr_floor - decoded.dest_floor2, 2));
				if (decoded.dest_floor3 != 10)
					destinations.push_back( make_pair(decoded.curr_floor - decoded.dest_floor3, 3));
				if (decoded.dest_floor4 != 10)
					destinations.push_back( make_pair(decoded.curr_floor - decoded.dest_floor4, 4));
				if (decoded.dest_floor5 != 10)
					destinations.push_back( make_pair(decoded.curr_floor - decoded.dest_floor5, 5));
				sort(destinations.begin(), destinations.end()); 
				// smallest to biggest difference for first, non negative.
				// First number in array indicates the floor we should stop to first.
				//Find first non-negative
				int non_neg = 0;
				for (int i = 0; i < destinations.size(); ++i){
					if (destinations[i].first > 0){
						non_neg = i;
						break;
					}
				}
				// Swap smallest with dest_floor
				int temp = decoded.dest_floor;
				if (destinations.size() > 0){
					decoded.dest_floor = destinations[non_neg].first;
					if (destinations[non_neg].second == 2)
						decoded.dest_floor2 = temp;
					if (destinations[non_neg].second == 3)
						decoded.dest_floor3 = temp;
					if (destinations[non_neg].second == 4)
						decoded.dest_floor4 = temp;
					if (destinations[non_neg].second == 5)
						decoded.dest_floor5 = temp;
				}
			}
			
			// int closest = destinations.back();
			// destinations.pop_back();

			if ((decoded.dest_floor - decoded.curr_floor)> 0){
				decoded.idle = true;
				decoded.curr_floor++;
				old = false;
			}
			else if ((decoded.dest_floor - decoded.curr_floor) < 0){
				decoded.idle = true;
				decoded.curr_floor--;
				old = false;
			}
			else
			{
				decoded.idle = false;
				if (decoded.closed && !old){
					decoded.closed = false;
					old = true;
				}
				if (decoded.passengers > 0)
					decoded.passengers--;

			}
		}
		decoded.up = (decoded.dest_floor - decoded.curr_floor) > 0 ? true: false;
		e1.Update_Status(&decoded);
		// updates named monitor elevator1
	} while (completion.Read() != 1);

	return 0;
}