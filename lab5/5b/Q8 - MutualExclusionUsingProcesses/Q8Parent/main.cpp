#include 	"..\..\..\..\RTExamples\rt.h"					// change pathlist to "rt.h" to suit location on your disk
#include "partB2.h"
#include "partB1.h"


int main()
{

	//atomic flag
	partB1 myB1;
	myB1.Resume();
	myB1.WaitForThread();

	//mutex
	partB2 myB2;
	myB2.Resume();
	myB2.WaitForThread();
	
	return 0;
}
