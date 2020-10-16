#include "partB1.h"


partB1::partB1()
{
	
}


partB1::~partB1()
{
}

int __thiscall partB1::Child1(void *args) {
	for (int i = 0; i < 5; i++) {
		while (atomicflag.test_and_set() == true);
		MOVE_CURSOR(10, 20);             	// move cursor to cords [x,y] = 10,20
		printf("B1 Child Thread 1");
		fflush(stdout);		      	// force output to be written to screen now
		atomicflag.clear();
		//Sleep(1000);
	}
	return 0;
}

int __thiscall partB1::Child2(void *args) {
	for (int i = 0; i < 5; i++) {
		while (atomicflag.test_and_set() == true);
		MOVE_CURSOR(10, 30);             	// move cursor to cords [x,y] = 10,30
		printf("B1 Child Thread 2");
		fflush(stdout);		      	// force output to be written to screen now
		atomicflag.clear();
		//Sleep(1000);
	}
	return 0;
}

int __thiscall partB1::Child3(void *args) {
	for (int i = 0; i < 5; i++) {
		while (atomicflag.test_and_set() == true);
		MOVE_CURSOR(10, 40);             	// move cursor to cords [x,y] = 10,40
		printf("B1 Child Thread 3");
		fflush(stdout);		      	// force output to be written to screen now
		atomicflag.clear();
		//Sleep(1000);
	}
	return 0;
}

int partB1::main() {
	ClassThread<partB1> child1(this, &partB1::Child1, ACTIVE, NULL);			// create the 3 other B1 Child Threads
	ClassThread<partB1> child2(this, &partB1::Child2, ACTIVE, NULL);				// create the 3 other B1 Child Threads
	ClassThread<partB1> child3(this, &partB1::Child3, ACTIVE, NULL);				// create the 3 other B1 Child Threads
	for (int i = 0; i < 5; i++) {
		while (atomicflag.test_and_set() == true);
		MOVE_CURSOR(5, 5);             	// move cursor to cords [x,y] = 5,5
		printf("Main Thread 1");
		fflush(stdout);		      	// force output to be written to screen now
		atomicflag.clear();
		//Sleep(1000);
	}
	child1.WaitForThread();				// wait for the 3 other B1 Child Threads to end
	child2.WaitForThread();
	child3.WaitForThread();


	return 0;

}