/***************************************************************************************
**	Program 1 - Example use of a CMutex object to enforce mutual exclusion
****************************************************************************************/
#include 	"..\..\rt.h"					// change pathlist to "rt.h" to suit location on your disk

struct 		mydatapooldata {			// data to be stored in a datapool
	unsigned long long int x;
};


int main()
{
	unsigned long long int a;

	//
	//	Start off with a datapool to represent our non-sharable resource. Now we need to make sure
	//	that only one process uses the datapool so we will need a mutex to protect it
	//

	CDataPool	dp1("MyDataPoolName", sizeof(struct mydatapooldata));		// create datapool
	struct 		mydatapooldata		*DataPtr = (struct mydatapooldata *)dp1.LinkDataPool();	// link to datapool

																							//	Create a semaphore 'mutex1' with initial value 1 meaning the resource is free
	CSemaphore   s1("mutex1", 1);


	DataPtr->x = 0;

	CProcess p1(					// create a child process
		"C:\\RTExamples\\Q8 - MutualExclusionUsingProcessesAndSemaphores\\debug\\Q8Child.exe",
		NORMAL_PRIORITY_CLASS,		// priority
		PARENT_WINDOW,					// process has it's own window
		ACTIVE						// process is active immediately
	);

	cout << "Parent Process Updating Resource.....\n";

	for (unsigned long long int i = 0; i < 400000ULL; i++) 		// access resource note REDUCE SIZE OF LOOP WHEN USING MUTEX OTHERWISE IT TAKES FOREVER
	{
		s1.Wait() ;			// gain access to resource

		a = DataPtr->x;
		a = a + 1;
		DataPtr->x = a;	// update resource

		s1.Signal() ;		// release resource

	}


	p1.WaitForProcess();			// wait for child process to die

	cout << "FINAL Value of x after PARENT AND CHILD PROCESS \nhave finished = " << DataPtr->x << endl;
	getchar();
	return 0;
}
