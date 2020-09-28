#include "..\rt.h"

//
//	To create an object with threads, you must have an active object with its own function main()
//	this will be run when a Resume() message is sent to the onject after it is constructed
//
//	Once main() is up and running it can create other threads using simple functions within the class
//	these functions, along with main() should be private: as we don't want the outside world invoking
//	these threads as if there were functions as that wouldn't really make sense
//
//	Once the threads have been created, the function main() can then wait for the thread to terminate
//	using WaitForThread() in the usual manner
//	In the example below, main() creates two threads out of or using the code for just one thread function
//	and passes it a pointer to some argument data, in this case just a message string
//
//	When the two threads terminate, then, in this instance, main() also terminates (but need not do so if you want
//	do other things) and thus the objects 'active'ness ceases to exist
// 
//	In the program main() (not the class main()), an instance of the active object is created.
//	To avoid race hazards  all active class are created in the suspended state to ensure that the 
//	constructor has a chance to complete initialisation of the object before the kernel starts running the thread function main()
//
//	This means that you have to Resume() and active object after you have created it (and of course you can Suspend() it also)
//
//	Note that when the function main() in the active class terminates, it does not mean that the object ceases to exist
//	An object is not destroyed until its destructor is called which is when the object goes out of scope or you physically
//	destroy it using 'delete' in the usual way. In the example below, it is only when program main() ends that the object is destroyed
//	not when the classes main() thread terminates.
//

class MyClassWithThreads : public ActiveClass {

	// put any attributes and member functions here that you like 
	// just like any other class along with constructors and destructors

private:
	int	MyClassData ;		// simple integer variable that is private to the class 


public:
	//	Constructor for the class that initialises the above variable with a given value

	MyClassWithThreads(int InitialData) : MyClassData(InitialData) {}

private:

	//	Here is the code for a function which will serve as our class thread
	//	it is always declared in the form int functionName(void *args) so that data can be passed to it
	//	and it can return an integer value indicating perhaps some exit status, success or otherwise
	//
	//	Remember the syntax 'void *' means the function gets given a void pointer which means it could be
	//	pointing to anything: ints, floats, arrays, strings, structures etc. In fact anything you wish
	//	however this means that the code must know what to expect and thus cast the void pointer into a pointer
	//	to the real data type it knows it has been given. In the exmapl below the code knows it will be given a message
	//	in the form of a char pointer and thus it casts it that way to gain access to the message


	int PrintMessageThread(void *ThreadArgs)
	{
		char *TheMessage = (char *)(ThreadArgs) ;	// get the message passed to the thread. Note cast from 'void *' to 'char *'

		for(int i = 0; i < 10000; i ++)
			cout << TheMessage << endl;

		return 0 ;									// thread ends here
	}

	int DisplayClassData(void *ThreadArgs)
	{
		for(int i = 0; i < 10000; i ++)
			cout << MyClassData << endl;			// print out the data for the class

		return 0 ;									// thread ends here
	}

// This is the main parent threaad for the class, when we create objects of this class
// this function is run. Here is creates two child threads of it's own which are just member functions
// of the same class and have access to the same class member variables, so they communicate with each other

	int main(void)	
	{
		char *Message1 = "Object threads are as easy as this....." ;
		char *Message2 = "It really is a concurrent world" ;

		//	Create two ACTIVE threads based around the code for the function 'PrintMessageThread' 
		//	Pass each thread a different message so it does something different to illustrate the concept
		//	also we have to pass to the thread the point 'this' as this will allow the thread
		//	to gain access to the private/public member variables and functions that you might have declared within the class
		//	This concept is demonstrated in the 3rd thread below

		ClassThread<MyClassWithThreads> My1stThread(this, &MyClassWithThreads::PrintMessageThread, ACTIVE, Message1) ;
//						^							  ^			                    ^				^		^---- argument to the thread
//						|							  |			                    |	            |------------ child thread is active
//						|							  |			                    |---------------------------- name of the child thread function
//						|							  |-------------------------------------- 'this' means this object
//						|-------------------------------------------------------------------- name of this classs


		ClassThread<MyClassWithThreads> My2ndThread(this, &MyClassWithThreads::PrintMessageThread, ACTIVE, Message2) ;


		//	create a 3rd thread in suspended state. No data is passed to this thread so we pass the value NULL as the last argument

		ClassThread<MyClassWithThreads> My3rdThread(this, &MyClassWithThreads::DisplayClassData, SUSPENDED, NULL) ;
		
		// wait for the above active threads to complete

		My1stThread.WaitForThread() ;
		My2ndThread.WaitForThread() ;
		
		// resume the 3rd thread and wait for it to complete
		My3rdThread.Resume() ;
		My3rdThread.WaitForThread() ;

		return 0 ;
	}
} ;



int main(void)
{
	// create 1st instance of the above active object on the heap using new and delete
	// then allow it to run and hen wait for it to terminate

	MyClassWithThreads	*object1 = new MyClassWithThreads(5) ;		// create an instance of the above class and pass it the value 5
	object1->Resume() ;

	cout << "Program main(): Waiting for Child object1 threads to terminate.....\n";
	object1->WaitForThread() ;

	delete object1 ;		// object1 destructor called here

	// create 2nd instance of the above active object on the stack
	// then allow it to run and hen wait for it to terminate

	MyClassWithThreads	object2(10) ;		// create an instance of the above class and pass it the value 10
	object2.Resume() ;

	cout << "Program main(): Waiting for Child object2 threads to terminate.....\n";
	object2.WaitForThread() ;
	
	cout << "Finished\n";

	// object2 destructor called at the end of program main()

	return 0 ;
}


