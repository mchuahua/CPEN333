// child3.cpp : Defines the entry point for the console application.
//
#include "..\..\..\..\RTExamples\rt.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{

	for (int i = 0; i < 200; ++i) {
		cout << "Hello from child process 3!!!!!!" << endl;
		Sleep(50);
	}
    return 0;
}

