#include 	"c:\RTExamples\rt.h"


UINT __stdcall ChildThread (void *args)	// A thread function 
{	
	int MyThreadNumber = *(int *)(args); 	
	
	for ( int i = 0; i < 10000; i ++)
		cout << "I am the Child thread: My thread number is " << MyThreadNumber << endl;

	return 0 ;
}

int 	main()
{
	int 	  Num[8] = {0,1,2,3,4,5,6,7} ;   // an array of integers
	
	CThread 	*Threads[8] ;	

//	Now here is the clever bit with threads. Let's create 8 instances of the above
//   thread code and let each thread know which number it is. 

	for ( int i = 0; i < 8; i ++) {
		cout << "Parent Thread: Creating Child Thread " << i << "in Active State\n";
		Threads[ i ] = new CThread (ChildThread, ACTIVE, &Num[i]) ;
	}
	
	// wait for threads to terminate, then delete thread objects we created above

	for( int j = 0; j < 8; j ++) {
		Threads[ j ] -> WaitForThread() ;	
		delete Threads[ j ] ;	// delete the object created by ‘new’
	}
	return 0 ;
}
