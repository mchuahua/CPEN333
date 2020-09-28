#include "c:\RTExamples\rt.h"

class 	CBankAccount   {
private:
	double	Balance ;	// the data to be protected, in this example a simple ‘double’, 
	CMutex	*theMutex;	// a pointer to a hidden mutex protecting the ‘Balance’ variable above

public:
	BOOL WithdrawFunds (double amount) 
	{ 
		theMutex -> Wait() ;
		BOOL Status = FALSE ;
		if (Balance >= amount) 	{
		        Status = TRUE ;
		        Balance = Balance - amount ;	
		}
		theMutex -> Signal() ;
		return Status ;
	} 

	void DepositFunds (double amount) 
	{
		theMutex -> Wait() ;
		Balance = Balance + amount ;
		theMutex -> Signal() ;
	}  
	
	void PrintBalance()
	{
		theMutex -> Wait() ;
		printf("Balance = %g\n", Balance) ;
		theMutex -> Signal() ;
	}

	// constructor and destructor
	CBankAccount () 
	{ 
		theMutex = new CMutex ("MyBankAccount") ; 
		Balance = 0.0 ; 
	}

	~CBankAccount () {
		delete theMutex; 
	}
} ;	

