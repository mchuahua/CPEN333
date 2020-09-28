#include "..\..\rt.h"

/////////////////////////////////////////////////////////////////////////////////////////
//	Example of writers readers mutex problem
/////////////////////////////////////////////////////////////////////////////////////////

// you should be able to see that more writers get access than readers when they compete
// at the end of the program, you will see a lot of readers eventually gain access when
// all writers have finished

CWritersReadersMutex r1("Paul") ;

class Reader : public ActiveClass 
{
	int main()
	{
		for(int i = 0; i < 100; i ++)	{
			r1.WaitToRead();
			putchar('R');
			r1.DoneReading() ;
		}
	
		return 0 ;							// terminate thread
	}
};


class Writer : public ActiveClass
{
	int main()
	{
		for(int i = 0; i < 100; i ++)	{
			r1.WaitToWrite();
			putchar('W');
			r1.DoneWriting() ;
		}
		return 0 ;							// terminate thread
	}
};



int main()
{
	
	Reader *TheReaders[100] ;
	Writer *TheWriters[100] ;


	for(int i = 0; i < 100; i ++) {
		TheWriters[i] = new Writer() ;
		TheReaders[i] = new Reader() ;
		TheReaders[i]->Resume() ;
		TheWriters[i]->Resume() ;
	}


	for(int i = 0; i < 100; i ++) {
		TheReaders[i]->WaitForThread() ;
		TheWriters[i]->WaitForThread() ;
	}
	
	return 0 ;
}
