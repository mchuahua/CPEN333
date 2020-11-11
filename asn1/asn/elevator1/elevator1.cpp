#include "../rt.h"
#include "../elevator.h"
#include <iostream>
#include <thread>

using namespace std;

void test();

int main()
{
	cout << "Hello from elevator1 process !!!!!!" << endl;
	CSemaphore completion("done", 0, 1);
	CSemaphore command("e1", 0, 1);

	elevator e1("ee2");

	thread t1(test);

	while(completion.Read() != 1){
		// Dispatcher signals command available from dispatcher
		command.Wait();
		// Updates status 
		e1.update_status(ELEVATOR1); 

		// updates named monitor elevator1
	}

	return 0;
}

void test(){

    CDataPool dp1("elevator1", sizeof(struct data));
	elevator1status = (struct data*)(dp1.LinkDataPool()); // get pointer to data pool




}