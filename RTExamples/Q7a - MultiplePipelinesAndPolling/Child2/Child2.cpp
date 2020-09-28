#include	"../../rt.h"			// change the pathlist to rt.h to suit location on your disk

int	main()
{
	cout << "Child2 Process Creating the Pipeline.....\n";
	CPipe	MyPipe("Pipe2");							// Create a pipe with the name "Pipe1"

	cout << "Parent Process Creating Child Process to Read from Pipeline.....\n";

	for (int x = 500; x < 10000; x++) {
		cout << "Child2 Writing " << x << " to pipeline\n";
		MyPipe.Write(&x, sizeof(x));
		Sleep(1800);
	}

	return 0;
}

