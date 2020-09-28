#include	"../../rt.h"	
	
int			pipe1data, pipe2data, pipe3data ;			// a single integer
char		KeyData ;


UINT __stdcall Thread1(void *)
{
	CPipe	p1("Pipe1" , 1024) ;			// create the three named pipelines 
	while( 1 )     {
		p1.Read(&pipe1data, sizeof(int)) ;		// read data from pipe 	
		cout << "Parent Thread 1: Read " << pipe1data << " from Pipe1\n";
	}
	return 0;
}

UINT __stdcall Thread2(void *)
{
	CPipe	p2("Pipe2" , 1024) ;			// create the three named pipelines 
	while( 1 )     {
		p2.Read(&pipe2data, sizeof(int)) ;		// read data from pipe 	
		cout << "Parent Thread 2: Read " << pipe1data << " from Pipe2\n";
	}
	return 0;
}

UINT __stdcall Thread3(void *)
{
	CPipe	p3("Pipe3" , 1024) ;			// create the three named pipelines 
	while( 1 )     {
		p3.Read(&pipe3data, sizeof(int)) ;		// read data from pipe 	
		cout << "Parent Thread 3: Read " << pipe1data << " from Pipe3\n";

	}
	return 0;
}
	
	
	
int	main()
{
	cout << "Parent Process Creating 3 Child Processes to write to their Pipeline.....\n";

	CProcess child1("C:\\RTExamples\\Q7a - MultiplePipelinesAndPolling\\Child1\\debug\\Child1.exe",	
			NORMAL_PRIORITY_CLASS,			// priority
			OWN_WINDOW,						// process has its own window					
			ACTIVE							// process is active immediately
	) ;

	CProcess child2("C:\\RTExamples\\Q7a - MultiplePipelinesAndPolling\\Child2\\debug\\Child2.exe",	
			NORMAL_PRIORITY_CLASS,			// priority
			OWN_WINDOW,						// process has its own window					
			ACTIVE							// process is active immediately
	) ;
	
	CProcess child3("C:\\RTExamples\\Q7a - MultiplePipelinesAndPolling\\Child3\\debug\\Child3.exe",	
			NORMAL_PRIORITY_CLASS,			// priority
			OWN_WINDOW,						// process has its own window					
			ACTIVE							// process is active immediately
	) ;

	//	Now generate an endless polling loop checking if any data has arrived from any of the four sources. 
	
	cout << "Parent Process Creating 3 Child threads to read from their Pipeline.....\n";

	CThread	t1(Thread1, ACTIVE, NULL) ;
	CThread	t2(Thread2, ACTIVE, NULL) ;
	CThread	t3(Thread3, ACTIVE, NULL) ;

	while( 1 )     {

		KeyData = getch() ;					// read next character from keyboard
		cout <<"Parent Thread Read " << KeyData << " from keyboard\n";
	}

	return 0 ;
}
