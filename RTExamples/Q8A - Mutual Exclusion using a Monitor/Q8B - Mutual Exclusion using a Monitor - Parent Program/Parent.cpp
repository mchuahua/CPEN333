#include "..\..\rt.h"
#include "..\BankAccount.h"

int main()
{
	BankAccount	b1("Fred") ;

	cout << "Parent Process: Setting Account Balance = $10.0\n";
	b1.SetBalance(10.0) ;

	CProcess p1("C:\\RTExamples\\Q8A - Mutual Exclusion using a Monitor\\Debug\\Q8A - Mutual Exclusion using a Monitor.exe",	// pathlist to child program executable				
			NORMAL_PRIORITY_CLASS,			// priority
			PARENT_WINDOW,						// process has its parent window					
			ACTIVE
	);	
	
	cout << "Parent Process depositing $100000 one $ at a time\n";
	
	for(int i = 0; i < 100000; i ++)
		b1.DepositFunds(1.0) ;

	p1.WaitForProcess() ;

	cout << "Balance = $" << b1.GetBalance() << endl ;

	return 0 ;
}