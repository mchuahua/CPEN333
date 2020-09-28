#include	"../rt.h"	
	
int			pipe1data, pipe2data, pipe3data ;			// a single integer
char		KeyData ;


UINT __stdcall Thread1(void *)
{
	CPipe	p1("Pipe1" , 1024) ;			// create the three named pipelines 
	while( 1 )     {
		p1.Read(&pipe1data, sizeof(int)) ;		// read data from pipe 	
		printf("Parent Thread 1: Read %d from Pipe 1\n", pipe1data) ;

	return 0
}

UINT __stdcall Thread2(void *)
{
	CPipe	p2("Pipe2" , 1024) ;			// create the three named pipelines 
	while( 1 )     {
		p2.Read(&pipe2data, sizeof(int)) ;		// read data from pipe 	
		printf("Parent Thread 2: Read %d from Pipe 2\n", pipe2data) ;

	return 0
}

UINT __stdcall Thread3(void *)
{
	CPipe	p3("Pipe3" , 1024) ;			// create the three named pipelines 
	while( 1 )     {
		p3.Read(&pipe3data, sizeof(int)) ;		// read data from pipe 	
		printf("Parent Thread 3: Read %d from Pipe 3\n", pipe3data) ;

	return 0
}
	
	
	
int	main()
{
	printf("Parent Process Creating Child Processes to write to the Pipeline.....\n") ;

	CProcess child1("C:\\RTExamples\\Q7aMultiplePipelinesAndPolling\\Child1\\debug\\Child1.exe",	
			NORMAL_PRIORITY_CLASS,			// priority
			OWN_WINDOW,						// process has its own window					
			ACTIVE							// process is active immediately
	) ;

	CProcess child2("C:\\RTExamples\\Q7aMultiplePipelinesAndPolling\\Child2\\debug\\Child2.exe",	
			NORMAL_PRIORITY_CLASS,			// priority
			OWN_WINDOW,						// process has its own window					
			ACTIVE							// process is active immediately
	) ;
	
	CProcess child3("C:\\RTExamples\\Q7aMultiplePipelinesAndPolling\\Child3\\debug\\Child3.exe",	
			NORMAL_PRIORITY_CLASS,			// priority
			OWN_WINDOW,						// process has its own window					
			ACTIVE							// process is active immediately
	) ;

	//	Now generate an endless polling loop checking if any data has arrived from any of the four sources. 
	
	printf("Parent Process Creating 3 Child threads to write to the Pipeline.....\n") ;

	CThread	t1(Thread1, ACTIVE, NULL) ;
	CThread	t2(Thread2, ACTIVE, NULL) ;
	CThread	t3(Thread3, ACTIVE, NULL) ;

	while( 1 )     {

		KeyData = getch() ;					// read next character from keyboard
		printf("Parent Thread Read '%c' from keyboard\n", KeyData);
	}

	return 0 ;
}
