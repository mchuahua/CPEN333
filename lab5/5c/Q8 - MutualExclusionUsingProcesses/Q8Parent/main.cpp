#include 	"..\..\..\..\RTExamples\rt.h"					// change pathlist to "rt.h" to suit location on your disk
#include "partC.h"


int main()
{
	partC myC("Muh thread");

	myC.Resume();
	myC.WaitForThread();
	
	return 0;
}
