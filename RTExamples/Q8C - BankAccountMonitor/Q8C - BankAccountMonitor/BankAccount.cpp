#include "CBankAccount.h"

CBankAccount	B1 ;	// a bank account object with built in 					


// synchronisation, i.e. a monitor			
UINT    __stdcall   Thread1(void *args)	// child  thread function
{
	for (int i = 0; i < 100000; i ++) {
		B1.WithdrawFunds(1.00) ;		// take 1 dollar from the account
	}
	return   0 ;
}

void main()				// primary thread within this process
{
	// start by putting 400k dollars in account
	B1.DepositFunds(400000) ;

	cout << "Starting.....\n";
	
	CThread          t1(Thread1, ACTIVE, NULL) ;	// create child thread
	CThread          t2(Thread1, ACTIVE, NULL) ;	// create child thread
	CThread          t3(Thread1, ACTIVE, NULL) ;	// create child thread

	for (int i = 0; i < 400000; i ++)	{
		B1.DepositFunds(1.00) ;		// add 1 dollar to the account
	}

	t1.WaitForThread() ;
	t2.WaitForThread() ;
	t3.WaitForThread() ;

	B1.PrintBalance() ;
	getchar();
}
