#include "..\rt.h"


////////////////////////////////////////////////////////////////////////////////////////////////
//	Example Use of the Dinning Philosophers problem
////////////////////////////////////////////////////////////////////////////////////////////////

CDinningPhilosophers dp1("Paul") ;


class Philosopher : public ActiveClass
{
	int MyPhilosopherNumber;

public: 
	Philosopher(int num)
	{
		MyPhilosopherNumber = num ;	// get my number given to me by parent (main())
									// this is given to the thread by the parent thread during the call
	}
	
private:
	int main(void)
	{
		for(int i = 0; i < 200; i ++)	{
			cout << "p" << MyPhilosopherNumber << " Thinking\n";
			SLEEP(100 * (1 + MyPhilosopherNumber)) ;
			dp1.Eat(MyPhilosopherNumber) ;
			cout << "p" << MyPhilosopherNumber << " Eating\n";
			SLEEP(250 * (1 + MyPhilosopherNumber)) ;
			dp1.DoneEating(MyPhilosopherNumber) ;
		}
	
		return 0 ;							// terminate thread
	}
};

int main()
{
	// create five philosophers
	Philosopher p0(0) ;
	Philosopher p1(1) ;
	Philosopher p2(2) ;
	Philosopher p3(3) ;
	Philosopher p4(4) ;

	p0.Resume() ;
	p1.Resume() ;
	p2.Resume() ;
	p3.Resume() ;
	p4.Resume() ;

	p0.WaitForThread() ;
	p1.WaitForThread() ;
	p2.WaitForThread() ;
	p3.WaitForThread() ;
	p4.WaitForThread() ;
	
	return 0 ;
}
