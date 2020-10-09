//	A Win32 C program to demonstrate the creation and use of name pipe. Error checking has 
//	been ommitted to aid clarity

#include 	"..\..\..\..\RTExamples\rt.h"		// change pathlist to "rt.h" file to suit location on disk

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
	char temp_n;
	double temp_m;

	printf("Child Process Opening Pipeline.....\n");
	CTypedPipe	<struct2>p2("MyPipe2", 1024);		// Create a pipe 'p1' with the name "MyPipe"
	struct2 pipe;
	for (int i = 0;; ++i) {
		temp_n = i;
		temp_m = (double)i + 1.0;

		pipe.n = temp_n;
		pipe.m = temp_m;

		p2.Write(&pipe);
		cout << "Wrote " << pipe.n << " " << pipe.m << endl;
		Sleep(4000);
	}

	Sleep(4000);
	return 0;

}	// pipe destructor called here to destroy p. Note however if pipeline still has unread data in it,
	// that data will be preserved
