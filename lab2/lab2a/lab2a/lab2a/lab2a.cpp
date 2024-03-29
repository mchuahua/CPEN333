// lab2a.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "..\..\..\..\RTExamples\rt.h"

using namespace std;

int main()
{
	cout << "Creating child processes as a parent" << endl;
	
	CProcess process1("child1.exe", NORMAL_PRIORITY_CLASS, OWN_WINDOW, ACTIVE);
	CProcess process2("child2.exe", NORMAL_PRIORITY_CLASS, OWN_WINDOW, ACTIVE);
	CProcess process3("child3.exe paul 1.2", NORMAL_PRIORITY_CLASS, OWN_WINDOW, ACTIVE);

	cout << "Child Processes started.....\n";

	cout << "Waiting For PartAChild1 to terminate....." << endl;
	process1.WaitForProcess();

	cout << "Waiting For PartAChild2 to terminate....." << endl;
	process2.WaitForProcess();

	cout << "Waiting For PartAChild3 to terminate....." << endl;
	process3.WaitForProcess();

	
	return 0;
}

