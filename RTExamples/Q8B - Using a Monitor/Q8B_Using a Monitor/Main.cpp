#include "../../rt.h"
#include "BankAccount.h"


BankAccount	B1("PaulsBankAccount") ;		// a monitor with built in synchronisation	

UINT    __stdcall   Thread1(void *args)	// child  thread function
{
	for (int i = 0; i < 100000; i ++) {
		B1.Deposit(1.00) ;		// add 1 dollar to the account
	}
	return   0 ;
}

void main()				// primary thread within this process
{
	CThread          t1(Thread1, ACTIVE, NULL) ;	// create child thread

	printf("Starting.....\n");

	for (int i = 0; i < 100000; i ++)	{
		B1.Deposit(1.00) ;		// add 1 dollar to the account
	}
	t1.WaitForThread() ;	// if thread already dead, then proceed, otherwise wait for it to finish
	printf("%f\n", B1.GetBalance()) ;
}


