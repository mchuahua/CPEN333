// child1.cpp : Defines the entry point for the console application.
//
#include "..\..\..\..\RTExamples\rt.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	for (int i = 0; i < 200; ++i) {
		cout << "Hello from child process 1!!!!!!" << endl;
		cout << "Argument passed in is ";
		for (i = 1; i< argc; i++) {
			cout << argv[i] << " ";
		}
		cout << endl;
		Sleep(50);
	}
    return 0;
}

