#include "partC.h"



partC::partC(string name)
{
	theMutex = new CMutex(string("__Mutex") + name);
}


partC::~partC()
{
	delete theMutex;
}

int __thiscall partC::Child1(void *args) {
	for (int i = 0; i < 5000; i++) {
		WriteToScreen(10, 20, string("child 1"));
	}
	return 0;
}

int __thiscall partC::Child2(void *args) {
	for (int i = 0; i < 5000; i++) {
		WriteToScreen(10, 30, string("child 2"));
	}
	return 0;
}

int __thiscall partC::Child3(void *args) {
	for (int i = 0; i < 5000; i++) {
		WriteToScreen(10, 40, string("child 3"));
	}
	return 0;
}
int partC::main() {
	ClassThread<partC> child1(this, &partC::Child1, ACTIVE, NULL);			// create the 3 other B1 Child Threads
	ClassThread<partC> child2(this, &partC::Child2, ACTIVE, NULL);				// create the 3 other B1 Child Threads
	ClassThread<partC> child3(this, &partC::Child3, ACTIVE, NULL);				// create the 3 other B1 Child Threads
	for (int i = 0; i < 5000; i++) {
		WriteToScreen(5, 5, "main thread");
	}
	child1.WaitForThread();				// wait for the 3 other B1 Child Threads to end
	child2.WaitForThread();
	child3.WaitForThread();
	return 0;
}
void partC::WriteToScreen(int x, int y, string input) {
		theMutex->Wait();
		MOVE_CURSOR(x, y);             	// move cursor to cords [x,y] 
		cout << input << " @ " << x << " " << y;
		//printf("%s @ ( %d , %d )", input, x, y);
		cout.flush();
		//fflush(stdout);		      	// force output to be written to screen now
		theMutex->Signal();
		Sleep(500);

}