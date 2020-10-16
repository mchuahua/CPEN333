//////////////////////////////////////////////////////////////////////////////////
//	The Consumer Process
//////////////////////////////////////////////////////////////////////////////////

#include 	<stdio.h>
#include	"..\..\..\RTExamples\rt.h"			// change pathlist to "rt.h" to suit location on disk

struct		mydatapooldata {			// template for data in a datapool
	int x;						// just a single int
	bool done = false;
};
struct		mydatapooldata2 {		// template for the data in a datapool
	int 	x;						// just a single int
};

struct		mydatapooldata 	*TheDataPointer;		// pointer to the actual data pool
struct		mydatapooldata2	*TheDataPointer2;		// pointer to the actual data pool

int main()
{
	CSemaphore		ps1("PS1", 0, 1);    // semaphore with initial value 0 and max value 1
	CSemaphore		cs1("CS1", 1, 1);    // semaphore with initial value 1 and max value 1
	CSemaphore		cs2("CS2", 1, 1);    // semaphore with initial value 1 and max value 1
	CSemaphore		ps2("PS2", 0, 1);    // semaphore with initial value 1 and max value 1
										 //	Create a datapool and then get a pointer to it

	CDataPool dp1("MyDataPoolName", sizeof(struct mydatapooldata));
	TheDataPointer = (struct mydatapooldata *)(dp1.LinkDataPool()); // get pointer to data pool

	cout << "Consumer Process Running.....\n";
	for (int i = 1; i < 10 && TheDataPointer->done != true;) {	// consume 10 lots of data
		Sleep(500);
		if (TheDataPointer->done == true)
			break;

		ps1.Wait();		// wait for producer process to signal producer semaphore
		cout << "Consumed: " << TheDataPointer->x << '\n';
		i = TheDataPointer->x;
		cs1.Signal();		// signal the consumer semaphore to wake up the producer
	}

	return 0;
}
