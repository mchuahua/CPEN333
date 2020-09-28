///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Example use of CThread
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include 	"..\..\rt.h"							// change pathlist to this header file according to where it is stored

CMutex	DVDWriter("DVDMutex") ;
CMutex	Scanner("ScannerMutex") ;

// below is a function that represents a child thread. Note carefully the way it has been written
// particularly the order in which the thread waits on each mutex to acquire the resource it protects

UINT __stdcall ThreadFn1(void *args)			// args points to any data passed to the child thread
{												// by the parent thread during the call
	while(1) {
		DVDWriter.Wait() ;
		if(Scanner.Wait(10) == WAIT_TIMEOUT)	{	// if we do not get the 2nd resource within 10 ms
			DVDWriter.Signal() ;						// give up the first resource 
			Sleep(rand()%10) ;						// wait some randon time between 0 and 10 ms
			continue ;								// try again by restarting from beginning of loop
		}

		cout << "1";
		DVDWriter.Signal() ;
		Scanner.Signal() ;
		Sleep(20) ;				
	}
	return 0 ;									// terminate child thread
}


UINT __stdcall ThreadFn2(void *args)			// args points to any data passed to the child thread
{												// by the parent thread during the call
	while(1) {
		Scanner.Wait() ;
		if(DVDWriter.Wait(10) == WAIT_TIMEOUT)	{	// if we do not get the 2nd resource within 10 ms
			Scanner.Signal() ;						// give up the first resource 
			Sleep(35) ;						// wait some randon time between 0 and 10 ms
			continue ;								// try again by restarting from beginning of loop
		}

		cout << "2";
		DVDWriter.Signal() ;
		Scanner.Signal() ;
		Sleep(20) ;
	}
	return 0 ;									// terminate child thread
}


int 	main()						// this is the processes main or parent thread
{
//	Now create a child thread to run concurrently with the main thread

	CThread	t1(ThreadFn1, ACTIVE, NULL) ;
	CThread	t2(ThreadFn2, ACTIVE, NULL) ;

	// now demonstrate passing data to a thread, anything will do provided we pass a pointer to it
	// in this case we will pass an integer

	cout << "Here, a thread will give up the resource it has\n";
	cout << "if it cannot acquire the other, so DEADLOCK should not happen\n\n";
	cout << "You should 1 or 2 indicating which thread has acquired both resources\n";
	
	t1.WaitForThread() ;			// wait for child thread to die
	t2.WaitForThread() ;			// wait for thread to die

	return 0 ;						// end the processes main thread
}