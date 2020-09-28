///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Example use of CThread
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include 	"..\rt.h"							// change pathlist to this header file according to where it is stored

//	below is a function that represents a child thread. Note carefully the way it has been written

UINT __stdcall ThreadFn1(void *args)			// args points to any data passed to the child thread
{												// by the parent thread during the call
	for(int i = 0; i < 500; i ++) {
		cout << "Hello from child thread 1.....\n";
		SLEEP(200) ;
	}
	return 0 ;									// terminate child thread
}


UINT __stdcall ThreadFn2(void *args)			// args points to any data passed to the child thread
{												// by the parent thread during the call
	for(int i = 0; i < 300; i ++) {
		cout << "Hello from child thread 2.....\n";
		SLEEP(200) ;
	}
	return 0 ;									// terminate child thread
}


UINT __stdcall ThreadFn3(void *args)			// args points to any data passed to the child thread
{												// by the parent thread during the call

	int theData = *(int *)(args) ;				// get the pointer passed to thread, convert to int pointer and get the int

	for(int i = 0; i < 300; i ++) {
		printf("Hello from child thread 3...I Have been given the data %d.....\n", theData) ;
		SLEEP(200) ;
	}
	return 0 ;									// terminate child thread
}

int 	main()						// this is the processes main or parent thread
{
	cout << "Parent Thread: Creating Child Thread 1 in Active State\n" ;

//	Now create a child thread to run concurrently with the main thread

	CThread	t1(ThreadFn1, ACTIVE, NULL) ;
	CThread	t2(ThreadFn2, ACTIVE, NULL) ;

	// now demonstrate passing data to a thread, anything will do provided we pass a pointer to it
	// in this case we will pass an integer


	
	int thread_data = 52 ;
	CThread	t3(ThreadFn3, ACTIVE, &thread_data) ;

	for(int i = 0; i < 400; i ++) {
		cout << "..........Hello from Parent thread .....\n" ;
		SLEEP(200) ;
	}

	t1.WaitForThread() ;			// wait for child thread to die
	t2.WaitForThread() ;			// wait for thread to die
	t3.WaitForThread() ;

	return 0 ;						// end the processes main thread
}