// child1.cpp : Defines the entry point for the console application.
//
#include "..\..\..\..\RTExamples\rt.h"
#include <iostream>

using namespace std;

int main()
{
	for (int i = 0; i < 200; ++i) {
		cout << "Hello from child process 1!!!!!!" << endl;
		Sleep(50);
	}
    return 0;
}

