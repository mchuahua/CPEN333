#include "..\rt.h"
#include <shared_mutex>

shared_mutex r1 ;

/////////////////////////////////////////////////////////////////////////////////////////
//	Example of readers/writers mutex problem
/////////////////////////////////////////////////////////////////////////////////////////

// you should be able to see that more readers get access than writers when they compete
// at the end of the program, you will see a lot of writers eventually gain access when
// all readers have finished

class Reader : public ActiveClass 
{
	int main()
	{
		for(int i = 0; i < 100; i ++)	{
			r1.lock_shared();
			putchar('R');
			r1.unlock_shared() ;
		}
		return 0 ;							// terminate thread
	}

};


class Writer : public ActiveClass 
{
	int main()
	{
		for(int i = 0; i < 100; i ++)	{
			r1.lock();
			putchar('W');
			r1.unlock() ;
		}
		return 0 ;							// terminate thread
	}
};


int main()
{
	
	Reader *TheReaders[100] ;
	Writer *TheWriters[100] ;

	int i ;

	for(i = 0; i < 100; i ++) {
		TheReaders[i] = new Reader() ;
		TheReaders[i]->Resume() ;
	}

	for(i = 0; i < 100; i ++) {
		TheWriters[i] = new Writer() ;
		TheWriters[i]->Resume() ;
	}

	for(i = 0; i < 100; i ++) {
		TheReaders[i]->WaitForThread() ;
		TheWriters[i]->WaitForThread() ;

		delete TheReaders[i] ;
		delete TheWriters[i] ;
	}
	
	return 0 ;
}
