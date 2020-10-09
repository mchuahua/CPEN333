#include 	"..\..\..\RTExamples\rt.h"		// change pathlist to "rt.h" file to suit location on disk
#include <thread>
struct		struct1 {		// structure template for some data that we intend to write to the pipeline
	int 	x;
	float 	y;
};

struct		struct2 {
	char	n;
	double  m;
};

int 	i = 5;									// a simple int
int 	array1[10] = { 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , 0 }; 		// array of 10 integers

char	name[15] = "Hello World";					// a string of 15 characters


CTypedPipe	<struct1>pipe1("MyPipe", 1024);							// Create a pipe 'p1' with the name "MyPipe"
CTypedPipe	<struct2>pipe2("MyPipe2", 1024);							// Create a pipe 'p1' with the name "MyPipe"

void struct1_read() {
	while (1) {
		struct1 temp;
		pipe1.Read(&temp);
		cout << "Pipe 1 Read " << temp.x << " " << temp.y << endl;
	}
}

void struct2_read() {
	while (1) {
		struct2 temp;
		pipe2.Read(&temp);
		cout << "Pipe 2 Read " << temp.n << " " << temp.m << endl;
	}
}


int 	main()
{
	


	cout << "Parent Process Creating Child Process to Read from Pipeline.....\n";

	CProcess p3("C:\\Users\\MartinChua\\Desktop\\CPEN333\\lab4\\4b\\4a\\debug\\pipeline_child.exe",	// pathlist to child program executable				
		NORMAL_PRIORITY_CLASS,			// priority
		OWN_WINDOW,						// process has its own window					
		ACTIVE							// process is active immediately
	);
	CProcess p4("C:\\Users\\MartinChua\\Desktop\\CPEN333\\lab4\\4b\\4a\\debug\\pipeline_child2.exe",	// pathlist to child program executable				
		NORMAL_PRIORITY_CLASS,			// priority
		OWN_WINDOW,						// process has its own window					
		ACTIVE							// process is active immediately
	);

	thread t1(struct1_read);
	thread t2(struct2_read);


	p3.WaitForProcess();
	p4.WaitForProcess();
	t1.join();
	t2.join();

	return 0 ;				// CDataPool object 'dp' destroyed here
}