/*
**	Win32 code program to solve the graphical problem illustrated previously. The single Producer
**	Single Consumer arrangement. Let's assume this is both the Producer and the Parent program
*/

#include 	<stdio.h>
#include	"..\..\..\RTExamples\rt.h"			// change pathlist to "rt.h" to suit location on disk

struct		mydatapooldata {		// template for the data in a datapool
	int 	x ;						// just a single int
	bool done = false;
} ;

struct		mydatapooldata2 {		// template for the data in a datapool
	int 	x;						// just a single int
};
struct		mydatapooldata3 {		// template for the data in a datapool
	int 	x;						// just a single int
	
};
struct		mydatapooldata 	*TheDataPointer ;		// pointer to the actual data pool
struct		mydatapooldata2	*TheDataPointer2;		// pointer to the actual data pool
struct		mydatapooldata3	*TheDataPointer3;		// pointer to the actual data pool

int 	main()
{
	CSemaphore		ps1("PS1", 0, 1) ;    // semaphore with initial value 0 and max value 1
	CSemaphore		cs1("CS1", 1, 1) ;    // semaphore with initial value 1 and max value 1
	CSemaphore		cs2("CS2", 1, 1);    // semaphore with initial value 1 and max value 1

	//CSemaphore		ps1("CS1", 1, 1);    // semaphore with initial value 1 and max value 1
	//CSemaphore		ps1("CS1", 1, 1);    // semaphore with initial value 1 and max value 1
	//CSemaphore		cs3("CS1", 1, 1);    // semaphore with initial value 1 and max value 1


//	Create a datapool and then get a pointer to it

	CDataPool dp1("MyDataPoolName", sizeof(struct mydatapooldata)) ;
	TheDataPointer = (struct mydatapooldata *)dp1.LinkDataPool() ;	// get pointer to data pool

//
//	Now that we have created the semaphores, let's create the child process
//

	CProcess p1("C:\\Users\\MartinChua\\Desktop\\CPEN333\\lab5\\5d\\Q9 - ProducerConsumerProblem\\Q9Child\\debug\\Q9Child.exe",	// pathlist to child program executable
		NORMAL_PRIORITY_CLASS,			// priority
		OWN_WINDOW,					// process has its own window
		ACTIVE							// process is active immediately
	) ;
	CProcess p2("C:\\Users\\MartinChua\\Desktop\\CPEN333\\lab5\\5d\\Q9 - ProducerConsumerProblem\\debug\\Q9Child2.exe",	// pathlist to child program executable
		NORMAL_PRIORITY_CLASS,			// priority
		OWN_WINDOW,					// process has its own window
		ACTIVE							// process is active immediately
	);
	printf("Producer Process Running.....\n") ;
	TheDataPointer->done = false;
	cout << "Single producer, double consumer" << endl;
	for(int i = 0; i < 10; i ++)	 {	// Produce 10 lots of data
		cs1.Wait() ;			// wait for consumer process to signal consumer semaphore
//		cout << "Hit RETURN to Produce Data.....\n";
//		getchar() ;
		TheDataPointer->x = i ;	// generate data and store in datapool
		cout << "Produced " << i << ".....\n";
		ps1.Signal() ;			// signal the producer semaphore to wake up the consumer
		
	}
	
	TheDataPointer->done = true;
	p1.WaitForProcess() ;		// wait for the child process to terminate if necessary
	p2.WaitForProcess();

	cout << "double producer, single consumer" << endl;



	return 0 ;				// sempahores destroyed here
}