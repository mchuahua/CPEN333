///////////////////////////////////////////////////////////////////////////////////////////
//	Example use of Creating threads, using Messages  and Timers
////////////////////////////////////////////////////////////////////////////////////////////
#include 	<stdio.h>		
#include 	"..\rt.h"				// change pathlist to rt.h to suit location on disk

#define 	END		1000

UINT __stdcall ThreadFn1(void *args)		// A child thread
{		
	UINT	Message = 0 ;		// A variable to holds message received in message queue

	CMailbox MyMailBox ;	// Create a message queue for this child thread
	CTimer	t1(500) ;		// set up and start a repetitive timer to go off at 1/2 second intervals

//	Now put the thread to sleep until a message arrives from Timer

	do {
		t1.WaitForTimer() ;
		cout << "ThreadFn1 Got Timer.....\n";		// thread woken up by timer
		
		// check for other message arriving while thread has been asleep (i.e. from parent thread)

		if(MyMailBox.TestForMessage() == TRUE)	{
			Message = MyMailBox.GetMessage() ;
			if(Message == END)
				cout << "ThreadFn1 Ending.....\n";
		}
	}while(Message != END) ;		// terminate loop and thus thread when END message received
	
	t1.StopTimer() ;				// stop the child threads timer	
	return 0 ;					// terminate child thread
}

UINT __stdcall ThreadFn2(void *args)	// A child thread
{		
	UINT	Message=0 ;

	CMailbox MyMailBox ;				// Create a message queue for this child thread
	CTimer	t1(50) ;				// set up repetitive timer to go off at 50mS intervals

//	Use above timer delay to generate in software other timing info. In this case, a timer that goes off
//	at 1/2 sec and 3/4 second intervals

	int Timer1 = 10 ;				// 10 ticks of 50mS timer = 1/2 second
	int Timer2 = 15 ;				// 15 ticks of 50mS timer = 3/4 second

	do {
		if(t1.TestForTimer() == TRUE)	{	// if this threads timer has gone off
			if( --Timer1 == 0)	{		// decrement timer1 until 10 ticks of real timer occur
				cout << "ThreadFn2 Got 1/2 sec Timer.....\n";
				Timer1 = 10 ;
			}
			if(--Timer2 == 0)	{		// decrement timer2 until 15 ticks of real timer occur
				cout << "ThreadFn2 Got 3/4 sec Timer.....\n";
				Timer2 = 15 ;
			}
		}

// Any other messages in message queue besides timers

		if(MyMailBox.TestForMessage() == TRUE)	{
			Message = MyMailBox.GetMessage() ;
			if(Message == END)
				cout << "ThreadFn2 Ending.....\n";
		}
		Sleep(1) ;				// sleep a small amount of time each time around loop (more efficient)
	}while(Message != END) ;	// terminate loop and thus thread when END message received
	
	t1.StopTimer() ;			// stop the child threads timer
	return 0 ;					// terminate child thread
}


int main()
{
	CMailbox    MyMailBox ;			// create a message queue for the main process thread
	CTimer	t1 ;						// create a timer (that is NOT yet running)

	cout << "Parent Thread: Creating Child Thread 1 and 2 in Active State\n";

	CThread	Child1(ThreadFn1, ACTIVE) ;		// Create child thread
	CThread	Child2(ThreadFn2, ACTIVE) ;		// Create child thread

	t1.SetTimer(10000) ;				// set timer going for 10 sec intervals
	t1.WaitForTimer();					// wait for this main threads timer has gone off
	cout << "main() Got Timer.....\n";

	Child1.Post(END) ;				// tell child thread to stop by sending END message
	Child2.Post(END) ;				// tell child thread to stop by sending END message
		
	t1.StopTimer() ;					// kill off the main threads timer
	
	cout << "Parent Thread: Waiting for child Threads to die.....\n";

	Child1.WaitForThread() ;			// wait for the child thread to die
	Child2.WaitForThread() ;			// wait for the child thread to die
	
	return 0 ;
}
