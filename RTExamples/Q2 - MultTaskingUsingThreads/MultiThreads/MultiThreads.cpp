#include "..\..\rt.h"

int   ThreadNum[11] = {0,1,2,3,4,5,6,7,8,9,10} ;  // an array of thread numbers, one passed to each thread to identify it

PerThreadStorage int MyThreadNumber ;	// How to allocate storage to each individual thread in the process including main thread

UINT __stdcall ChildThread (void *args)	// thread function 
{	
	MyThreadNumber = *(int *)(args); 	
	
	for ( int i = 0; i < 100; i ++)	{
		cout << "I am the Child thread: My thread number is " << MyThreadNumber << endl ;
		Sleep(200) ;
	}

	return 0 ;
}


int main()
{
	CThread 	*Threads[11] ;
	int i ;

//	Now here is the clever bit with threads. 
//  Let's create 8 instances of the above thread code and 
//  let each thread know who it is by passing it a number, this could then be
//	used to influence the action of the read such as reading a different port number. 

	for(i = 0; i < 11; i ++) {
		cout << "Parent Thread: Creating Child Thread 1 in Active State\n";
		Threads[i] = new CThread(ChildThread, ACTIVE, &ThreadNum[i]) ;
//									^			^		^----------------pass an integer by reference
//									|			|------------------------State of the thread active/suspended
//									|------------------------------------The name of the function acting as a thread
	}
	
	// wait for threads and then delete thread objects we created above

	for(i = 0; i < 11; i ++)
		Threads[i]->WaitForThread() ;
	
	return 0 ;
}
