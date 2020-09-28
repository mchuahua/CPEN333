#include "..\..\rt.h"

#define NUMBER_OF_PHILOS 5	// start of with 5 philosophers

CMutex	*Chopsticks[NUMBER_OF_PHILOS] ;		// create a mutex to protect each chopstick

//	A class to represent a philosopher

class Philosopher : public ActiveClass
{
	int MySeatNumber ;

public: 

// constructor
	Philosopher(int _MySeatNumber) {
		MySeatNumber = _MySeatNumber ;		// figure out which philosopher I am, in range (0 to (NUMBER_OF_PHILOSOPHERS - 1))
	}

private: 
	//	These functions return the index of the chopstick mutex to the left and right of the current philospher

	int LeftChopstick() {		return ((MySeatNumber + NUMBER_OF_PHILOS - 1) % NUMBER_OF_PHILOS) ;	}
	int RightChopstick() {		return ((MySeatNumber + 1) % NUMBER_OF_PHILOS) ;}

	int main(void)
	{
		// Now get the indexes into the array for chopstick semaphores for my left and right chopsticks

		int MyLeftChopstickNumber = LeftChopstick() ;
		int MyRightChopstickNumber = RightChopstick() ;

		//	Now get the Win32 'Handles' for those left and right chopstick semaphores and put them into an array
		//	this is needed for the Wait_for_multiple_objects call below

		HANDLE MyChopstickHandles[2] = {  
				Chopsticks[MyLeftChopstickNumber]->GetHandle(), 
				Chopsticks[MyRightChopstickNumber]->GetHandle() 
		} ;

		//	Now simulate actions of eating and thinking at varying times

		for(int i = 0; i < 10; i++)	{
			SLEEP(300 + (MySeatNumber * 300))	;		// simulate thinking, this is a different time delay for each philosopher

		// Now simulate Eating by acquiring chopsticks to left and right of me

			WAIT_FOR_MULTIPLE_OBJECTS(2, MyChopstickHandles, INFINITE) ;
			cout << "p" << MySeatNumber << " ";			// show philosopher is eating by printing his number
			SLEEP(300 + (MySeatNumber * 10)) ;		// simulate eating, this is a different time delay for each philosopher
		
			Chopsticks[MyLeftChopstickNumber]->Signal() ;	// put down left chopstick, i.e. release the resource after eating
			Chopsticks[MyRightChopstickNumber]->Signal() ;	// put down right chopstick, i.e. release the resource after eating
		}
		return 0 ;
	}
};


int main()
{
	int i ;
	Philosopher *thePhilosophers[NUMBER_OF_PHILOS] ;	// array of pointers to philosopher object (not yet constructed)

	for(i = 0; i < NUMBER_OF_PHILOS; i ++)	{	// initialise philosopher numbers
		//	Create the numbered Mutex's above
		char buff[80] ;
		sprintf(buff, "Chopstick%d", i) ;			// generate the name for the mutex based on the number
		Chopsticks[i] = new CMutex(buff) ;			// create the mutexs

		thePhilosophers[i] = new Philosopher(i) ;	// create the philosopher threads with their seat number
	}

	for(i = 0; i < NUMBER_OF_PHILOS; i ++)	{	// wait for philosophers to terminate
		thePhilosophers[i]->Resume() ;
	}

	for(i = 0; i < NUMBER_OF_PHILOS; i ++)	{	// wait for philosophers to terminate
		thePhilosophers[i]->WaitForThread() ;
		delete thePhilosophers[i] ;
	}

	for(i = 0; i < NUMBER_OF_PHILOS; i ++)		// delete the chopsticks at the end
		delete Chopsticks[i];	
	
	return 0 ;
}