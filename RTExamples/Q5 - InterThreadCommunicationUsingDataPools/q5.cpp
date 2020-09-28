#include 	"..\rt.h"		// change pathlist to "rt.h" file to suit location on disk

// Let's suppose the data we want to put in the datapool is complex, i.e not just a simple
// int or char. The easiest way to store complex data is to introduce a structure template
// describing the names and types of the data we wich to group together as shown below
//  which includes three variables, two simple integers and an array of 10 integers
  
struct 	    mydatapooldata 	{		// start of structure template
		int floor ;				// floor corresponding to lifts current position
		int direction ;			// direction of travel of lift
		int floors[10] ;			// an array representing the floors and whether requests are set 
} ;	


//
//	A global variable that parent and child thread can use
//

struct mydatapooldata	GlobalData ;

UINT __stdcall ChildThread(void *args)
{
	int i ;

// 	Attempt to make the datapool 'Car1'. This process will not know
//	whether the datapool exists or not yet (we know that it does because we only
//	set the process running after the parent program had created it and stored data
//	in it) but that shouldn't matter, since the program can just attempt to make it. If it already exists
//	then it will simply use it. If it doesn't exist, then it will be created below


	cout << "Child Thread.....\n";
	cout << "Child Read value for Floor = " << GlobalData.floor << endl;
	cout << "Child Read value for Direction = " << GlobalData.direction << endl; 

	cout << "Child Read values for floor array = ";

	for(i=0; i < 10; i ++)
		cout << GlobalData.floors[ i ] << " ";

// The CDatapool object 'dp' created at the start of the program will now be destroyed
// and provided there are no other processes using the same named datapool, then that datapool
// will also be destroyed
	
	getchar();			// pause seconds so programmer can view output before child dies

	return 0 ;
}						// end of structure template

int 	main()
{
	cout << "Parent Thread.....\n";
	cout << "Parent Writing value '55' to floor variable.....\n";
	GlobalData.floor = 55 ;		// store 55 into the variable 'floor' in the datapool

	cout << "Parent Writing value '1' to direction variable.....\n";
	GlobalData.direction = 1 ;		// store 1 into the variable 'direction' in the datapool

	cout << "Parent Writing value '0 1 2 3 4 5 6 7 8 9' to floors array.....\n";
	for(int i = 0; i < 10; i ++)
		GlobalData.floors[ i ] = i ;	

//	a child thread that can access the data

	cout << "Creating Child thread.....\n\n";
	CThread	c1(ChildThread,			// name of function representing the thread
			   ACTIVE,				// thread is created in ACTIVE state (could use SUSPENDED)
			   NULL					// Pass no arguments to the thread function
	) ;

	 
	c1.WaitForThread() ;		// wait for the child process to Terminate
	return 0 ;				// CDataPool object 'dp' destroyed here
}