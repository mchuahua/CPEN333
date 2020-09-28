#include "..\rt.h"

CRendezvous     r1("MyRendezvous", 5) ;		// Attempt to create a rendezvous object involving 5 threads

class RendezvousThread : public ActiveClass		// A thread to use a rendezvous, args points to an int to identify the thread number
{
	int MyThreadNumber;

public:
// constructor to initialise my thread number which affects how long I take to arrive at the rendezvous

	RendezvousThread(int _MyThreadNumber) { MyThreadNumber = _MyThreadNumber ; }

	int main()
	{
		for(int i = 0; i < 10; i ++)	{
			SLEEP(1000 * MyThreadNumber) ;								// sleep for an amount of time based on my thread number
			cout << "\nThread " << MyThreadNumber << " Arriving at Rendezvous.....";		// do something after being released, i.e. print my threadnumber
			r1.Wait();													// wait at the rendezvous point
			cout << "\nGo " <<MyThreadNumber;
		}																// go back at wait again (10 times)
		return 0 ;														// terminate thread
	}
} ;

int main()
{
	RendezvousThread t1(1) ;	// create 5 threads and pass them a thread number
	RendezvousThread t2(2) ;
	RendezvousThread t3(3) ;
	RendezvousThread t4(4) ;
	RendezvousThread t5(5) ;

	t1.Resume() ;
	t2.Resume() ;
	t3.Resume() ;
	t4.Resume() ;
	t5.Resume() ;


	t1.WaitForThread() ;
	t2.WaitForThread() ;
	t3.WaitForThread() ;
	t4.WaitForThread() ;
	t5.WaitForThread() ;

	
	return 0 ;
}
