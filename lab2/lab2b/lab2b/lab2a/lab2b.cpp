// lab2b.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "cprocess.h"

using namespace std;

int main()
{
	cout << "Creating child processes as a parent" << endl;
	
	CProcess process1("child1.exe", NORMAL_PRIORITY_CLASS, PARENT_WINDOW, SUSPENDED);
	CProcess process2("child2.exe", NORMAL_PRIORITY_CLASS, PARENT_WINDOW, SUSPENDED);


	cout << "Child Processes created but suspended....\n";

	cout << "Unsuspending Child1 then terminating....." << endl;
	process1.Resume();
	process1.WaitForProcess();

	cout << "Unsuspending Child2 then terminating....." << endl;
	process2.Resume();
	process2.WaitForProcess();


	
	return 0;
}

