//////////////////////////////////////////////////////////////////////////////////
//	The Consumer Process
//////////////////////////////////////////////////////////////////////////////////

#include 	<stdio.h>
#include	"..\..\..\..\RTExamples\rt.h"			// change pathlist to "rt.h" to suit location on disk

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
	CSemaphore		ps2("PS2", 0, 1);    // semaphore with initial value 0 and max value 1
										 //	Create a datapool and then get a pointer to it

	CDataPool dp1("MyDataPoolName", sizeof(struct mydatapooldata));
	TheDataPointer = (struct mydatapooldata *)(dp1.LinkDataPool()); // get pointer to data pool
	
	CDataPool dp2("MyDataPoolName", sizeof(struct mydatapooldata));
	TheDataPointer2 = (struct mydatapooldata2 *)(dp2.LinkDataPool()); // get pointer to data pool


	cout << "Producer Process (2) Running.....\n";
	for (int i = 0; i < 10; i++) {	// Produce 10 lots of data
		cs2.Wait();			// wait for consumer process to signal consumer semaphore
							//		cout << "Hit RETURN to Produce Data.....\n";
							//		getchar() ;
		TheDataPointer->x = i;	// generate data and store in datapool
		cout << "Produced " << i << ".....\n";
		ps2.Signal();			// signal the producer semaphore to wake up the consumer

	}

	
	return 0;
}
