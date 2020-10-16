#include "partB2.h"



partB2::partB2()
{
	theMutex = new CMutex("mutexinside");
}


partB2::~partB2()
{
	delete theMutex;
}

int __thiscall partB2::Child1(void *args) {
	for (int i = 0; i < 5; i++) {
		theMutex->Wait();
		MOVE_CURSOR(10, 20);             	// move cursor to cords [x,y] = 10,20
		printf("B2 Child Thread 1");
		fflush(stdout);		      	// force output to be written to screen now
		theMutex->Signal();
		//Sleep(1000);
	}
	return 0;
}

int __thiscall partB2::Child2(void *args) {
	for (int i = 0; i < 5; i++) {
		theMutex->Wait();
		MOVE_CURSOR(10, 30);             	// move cursor to cords [x,y] = 10,30
		printf("B2 Child Thread 2");
		fflush(stdout);		      	// force output to be written to screen now
		theMutex->Signal();
		//Sleep(1000);
	}
	return 0;
}

int __thiscall partB2::Child3(void *args) {
	for (int i = 0; i < 5; i++) {
		theMutex->Wait();
		MOVE_CURSOR(10, 40);             	// move cursor to cords [x,y] = 10,40
		printf("B2 Child Thread 3");
		fflush(stdout);		      	// force output to be written to screen now
		theMutex->Signal();
		//Sleep(1000);
	}
	return 0;
}

int partB2::main() {
		ClassThread<partB2> child1(this, &partB2::Child1, ACTIVE, NULL);			// create the 3 other B2 Child Threads
		ClassThread<partB2> child2(this, &partB2::Child2, ACTIVE, NULL);				// create the 3 other B2 Child Threads
		ClassThread<partB2> child3(this, &partB2::Child3, ACTIVE, NULL);				// create the 3 other B2 Child Threads
		for (int i = 0; i < 50000; i++) {
			theMutex->Wait();
			MOVE_CURSOR(5, 5);             	// move cursor to cords [x,y] = 5,5
			printf("Main Thread 1");
			fflush(stdout);		      	// force output to be written to screen now
			theMutex->Signal();
			//Sleep(1000);
		}
		child1.WaitForThread();				// wait for the 3 other B2 Child Threads to end
		child2.WaitForThread();
		child3.WaitForThread();

		
		return 0;

}