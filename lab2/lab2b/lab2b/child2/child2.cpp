// child2.cpp : Defines the entry point for the console application.
//
#include "..\..\..\..\RTExamples\rt.h"
#include <iostream>

using namespace std;


int main()
{
	for (int i = 0; i < 10; ++i) {
		cout << "Hello from child process 2!!!!!!" << endl;
		Sleep(50);
	}
}

