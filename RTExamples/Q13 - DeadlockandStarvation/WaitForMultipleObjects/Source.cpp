///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Example use of CThread
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include 	"..\..\rt.h"							// change pathlist to this header file according to where it is stored

// global Mutexes
CMutex	DVDWriter("DVDMutex");
CMutex	Scanner("ScannerMutex");

// global array of Mutex Handles (i.e. identifiers) for above 2 mutexes, initialised in main()
HANDLE TheMutexHandles[2];

//	below is a function that represents a child thread. Note carefully the way it has been written

UINT __stdcall ThreadFn1(void* args)			// args points to any data passed to the child thread
{												// by the parent thread during the call
	while (1) {
		// wait forever for the two mutexes
		WAIT_FOR_MULTIPLE_OBJECTS(2, TheMutexHandles, INFINITE);
		cout << "1";
		DVDWriter.Signal();
		Scanner.Signal();
		Sleep(20);
	}
	return 0;									// terminate child thread
}


UINT __stdcall ThreadFn2(void* args)			// args points to any data passed to the child thread
{												// by the parent thread during the call
	while (1) {
		WAIT_FOR_MULTIPLE_OBJECTS(2, TheMutexHandles, INFINITE);
		cout << "2";
		DVDWriter.Signal();
		Scanner.Signal();
		Sleep(40);
	}
	return 0;									// terminate child thread
}


int 	main()						// this is the processes main or parent thread
{

	TheMutexHandles[0] = Scanner.GetHandle(); 		// get handle/ID of each mutex
	TheMutexHandles[1] = DVDWriter.GetHandle();

	//	Now create a child thread to run concurrently with the main thread

	CThread	t1(ThreadFn1, ACTIVE, NULL);
	CThread	t2(ThreadFn2, ACTIVE, NULL);

	// now demonstrate passing data to a thread, anything will do provided we pass a pointer to it
	// in this case we will pass an integer

	cout << "Here each Thread acquires both mutexes with one call so DEADLOCK should NOT happen\n";
	cout << "Note this is not the same as treating both resources as a single resource\n";
	cout << "Since other threads - not those here - could still acquire individual mutexes without problem\n\n";
	cout << "It's also more effecient that relinquising a resource and trying later, since that approach";
	cout << "Involves polling which is never good";

	cout << "You should see sequences of '1' or '2' as the two threads acquire both resources\n";
	cout << "If the output stops, the two theads have becomes DEADLOCKED\n";

	t1.WaitForThread();			// wait for child thread to die
	t2.WaitForThread();			// wait for thread to die

	return 0;						// end the processes main thread
}