#include 	"..\..\..\RTExamples\rt.h"		// change pathlist to "rt.h" file to suit location on disk
#include <string>

// Let's suppose the data we want to put in the datapool is complex, i.e not just a simple
// int or char. The easiest way to store complex data is to introduce a structure template
// describing the names and types of the data we wich to group together as shown below
//  which includes three variables, two simple integers and an array of 10 integers
  
struct 	    mydatapooldata 	{		// start of structure template
		
		bool yesorno;
		int random_integer;
		char char_array[10];
		
} ;							// end of structure template

struct		example {		// structure template for some data that we intend to write to the pipeline
	int 	x;
	float 	y;
};

int 	i = 5;									// a simple int
int 	array1[10] = { 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , 0 }; 		// array of 10 integers

char	name[15] = "Hello World";					// a string of 15 characters
struct	 example mystruct = { 2, 5.5 };				// a structure with an int and a float in it

int 	main()
{
	//////////////////////////////////////////////////////////
	//4a (1)
	cout << "Parent attempting to create/use the datapool.....\n";
	CDataPool 		dp("Car1", sizeof(struct mydatapooldata)) ;
	
	struct mydatapooldata 	 *MyDataPool = (struct mydatapooldata *)(dp.LinkDataPool()) ;

	printf("Parent linked to datapool at address %p.....\n", MyDataPool) ;

	cout << "Parent writing values";
	MyDataPool->yesorno = false;
	MyDataPool->random_integer = 420;
	MyDataPool->char_array[0] = 'h';
	MyDataPool->char_array[1] = 'i';
	MyDataPool->char_array[2] = ' ';
	MyDataPool->char_array[3] = 't';
	MyDataPool->char_array[4] = 'h';
	MyDataPool->char_array[5] = 'e';
	MyDataPool->char_array[6] = 'r';
	MyDataPool->char_array[7] = 'e';
	MyDataPool->char_array[8] = ' ';
	MyDataPool->char_array[9] = '!';

	getchar() ;

	CProcess p1("C:\\Users\\MartinChua\\Desktop\\CPEN333\\lab4\\4a\\4a\\Q4\\debug\\q4.exe",	// pathlist to child program executable
		NORMAL_PRIORITY_CLASS,			// priority
		OWN_WINDOW,						// process has its own window
		ACTIVE							// process is active immediately
	) ;

	CProcess p2("C:\\Users\\MartinChua\\Desktop\\CPEN333\\lab4\\4a\\4a\\Q4\\debug\\q4.exe",	// pathlist to child program executable
		NORMAL_PRIORITY_CLASS,			// priority
		OWN_WINDOW,						// process has its own window
		ACTIVE							// process is active immediately
	);

	p1.WaitForProcess() ;		// wait for the child process to Terminate
	p2.WaitForProcess();

	//////////////////////////////////////////////////////////
	//4a (2)
	cout << "Parent Process Creating the Pipeline.....\n";
	CPipe	pipe1("MyPipe", 1024);							// Create a pipe 'p1' with the name "MyPipe"
	CPipe	pipe2("MyPipe2", 1024);							// Create a pipe 'p1' with the name "MyPipe"

	cout << "Parent Process Creating Child Process to Read from Pipeline.....\n";

	CProcess p3("C:\\Users\\MartinChua\\Desktop\\CPEN333\\lab4\\4a\\4a\\debug\\pipeline_child.exe",	// pathlist to child program executable				
		NORMAL_PRIORITY_CLASS,			// priority
		OWN_WINDOW,						// process has its own window					
		ACTIVE							// process is active immediately
	);
	CProcess p4("C:\\Users\\MartinChua\\Desktop\\CPEN333\\lab4\\4a\\4a\\debug\\pipeline_child2.exe",	// pathlist to child program executable				
		NORMAL_PRIORITY_CLASS,			// priority
		OWN_WINDOW,						// process has its own window					
		ACTIVE							// process is active immediately
	);

	cout << "Hit RETURN to Write the integer " << i << " to the pipeline.....\n";
	getchar();

	pipe1.Write(&i, sizeof(i));						// write the int 'i' to the pipe
	pipe2.Write(&i, sizeof(i));						// write the int 'i' to the pipe

	cout << "Hit RETURN to Write the integer array 1 2 3 4 5 6 7 8 9 0 to the pipeline.....\n";
	getchar();

	pipe1.Write(&array1[0], sizeof(array1));			// write the array of integers' to the pipe
	pipe2.Write(&array1[0], sizeof(array1));			// write the array of integers' to the pipe

	cout << "Hit RETURN to Write the string " << name << " to the pipeline.....\n";
	getchar();

	pipe1.Write(&name[0], sizeof(name));				// write the string to the pipe
	pipe2.Write(&name[0], sizeof(name));				// write the string to the pipe

	cout << "Hit RETURN to Write the structure [" << mystruct.x << ", " << mystruct.y << "] to the pipeline.....\n";
	getchar();

	pipe1.Write(&mystruct, sizeof(mystruct));			// write the structure to the pipeline
	pipe2.Write(&mystruct, sizeof(mystruct));			// write the structure to the pipeline


	p3.WaitForProcess();

	return 0 ;				// CDataPool object 'dp' destroyed here
}