#include	"../rt.h"	
	
int			pipe1data, pipe2data, pipe3data ;			// a single integer
char		KeyData ;


	
int	main()
{
	CPipe	p1("Pipe1" , 1024) ;		// create the three named pipelines 
	CPipe	p2("Pipe2" , 1024) ;
	CPipe	p3("Pipe3" , 1024) ;

	cout << "Parent Process Creating Child Processes to write to the Pipeline.....\n";

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
	
	cout << "Parent Process Creating 3 Child threads to write to the Pipeline.....\n";

	while( 1 )     {
		if ((p1.TestForData()) >= sizeof(pipe1data) )	{		// if at least 1 integer in pipeline
			p1.Read(&pipe1data , sizeof(pipe1data)) ;		// read data from pipe 	
			cout << "Parent Read " << pipe1data << " from Pipe1\n";
		}

		if ((p2.TestForData()) >= sizeof(pipe2data) )	{	// if at least 1 integer in pipeline
			p2.Read(&pipe2data , sizeof(pipe2data)) ;		// read data from pipe
			cout << "Parent Read " << pipe2data << " from Pipe2\n";
		}

		if ((p3.TestForData()) >= sizeof(pipe3data) )	{		// if at least 1 integer in pipelinee 
			p3.Read(&pipe3data , sizeof(pipe3data)) ;		// read data from pipe
			cout << "Parent Read " << pipe3data << " from Pipe3\n";
		}

		if (TEST_FOR_KEYBOARD() != 0) {
			KeyData = getch() ;					// read next character from keyboard
			cout << "Parent Read " << KeyData << " from keyboard\n";
		}
	}

	return 0 ;
}
