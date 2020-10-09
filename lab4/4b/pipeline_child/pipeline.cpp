//	A Win32 C program to demonstrate the creation and use of name pipe. Error checking has 
//	been ommitted to aid clarity

#include 	"..\..\..\RTExamples\rt.h"		// change pathlist to "rt.h" file to suit location on disk

struct		struct1 {		// structure template for some data that we intend to write to the pipeline
	int 	x;
	float 	y;
};

struct		struct2 {
	char	n;
	double  m;
};

int	main()
{
	int temp_x;
	float temp_y;

	printf("Child Process Opening Pipeline.....\n");
	CTypedPipe	<struct1>p1("MyPipe", 1024);		// Create a pipe 'p1' with the name "MyPipe"
	struct1 pipe;
	for(int i = 0 ;; ++i){
		temp_x = i;
		temp_y = (float)i + (float)1.2;
		
		pipe.x = temp_x;
		pipe.y = temp_y;

		p1.Write(&pipe);
		cout << "Wrote " << pipe.x << " " << pipe.y << endl;
		Sleep(3000);
	}

	Sleep(4000);
	return 0;

}	// pipe destructor called here to destroy p. Note however if pipeline still has unread data in it,
	// that data will be preserved
