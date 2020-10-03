// lab2e.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "cthread.h"
#include <string>

using namespace std;

struct myStruct{
	int i = 0;
	string myString = "hello";
	char myChar = 'x';
} aStruct;

unsigned int __stdcall ChildThread1(void *args)	// A thread function 
{
	myStruct MyThreadStruct = *(myStruct *)(args);

	for (int i = 0; i < 1000; i++)
		cout << "Child1: My struct number is " << MyThreadStruct.i << endl;

	return 0;
}

unsigned int __stdcall ChildThread2(void *args)	// A thread function 
{
	myStruct MyThreadStruct = *(myStruct *)(args);

	for (int i = 0; i < 1000; i++)
		cout << "Child2: My struct string is " << MyThreadStruct.myString << endl;

	return 0;
}

unsigned int __stdcall ChildThread3(void *args)	// A thread function 
{
	myStruct MyThreadStruct = *(myStruct *)(args);

	for (int i = 0; i < 1000; i++)
		cout << "Child3: My struct char is " << MyThreadStruct.myChar << endl;

	return 0;
}


int 	main()
{
	//int 	  Num[8] = { 0,1,2,3,4,5,6,7 };   // an array of integers

	CThread 	*Threads[24];

	//	Now here is the clever bit with threads. Let's create 8 instances of the above
	//   thread code and let each thread know which number it is. 

	for (int i = 0; i < 8; i++) {
		cout << "Parent Thread: Creating Child Thread " << i << "in Active State\n";
		Threads[i*3] = new CThread(ChildThread1, ACTIVE, &aStruct);
		Threads[i*3+1] = new CThread(ChildThread2, ACTIVE, &aStruct);
		Threads[i*3+2] = new CThread(ChildThread3, ACTIVE, &aStruct);
	}

	// wait for threads to terminate, then delete thread objects we created above

	for (int j = 0; j < 8; j++) {
		Threads[j]->WaitForThread();
		delete Threads[j];	// delete the object created by ‘new’
	}
	return 0;
}
