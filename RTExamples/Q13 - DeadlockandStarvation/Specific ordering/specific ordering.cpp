///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Example use of CThread
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include 	"..\..\rt.h"							// change pathlist to this header file according to where it is stored

CMutex	DVDWriter("DVDMutex") ;
CMutex	Scanner("ScannerMutex") ;

//	below is a function that represents a child thread. Note carefully the way it has been written

UINT __stdcall ThreadFn1(void *args)			// args points to any data passed to the child thread
{												// by the parent thread during the call
	while(1) {
		DVDWriter.Wait() ;
		Scanner.Wait() ;
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
		DVDWriter.Wait() ;
		Scanner.Wait() ;
		cout << "2";
		DVDWriter.Signal() ;
		Scanner.Signal() ;
		Sleep(40) ;
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

	cout << "Here threads attempt to acquire resources in the SAME order so DEADLOCK should NOT happen\n";
	
	t1.WaitForThread() ;			// wait for child thread to die
	t2.WaitForThread() ;			// wait for thread to die

	return 0 ;						// end the processes main thread
}