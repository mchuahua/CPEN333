#ifndef __BankAccount__
#define __BankAccount__

#include "..\..\rt.h"

class 	BankAccount   {
private:
	struct theData {
		double Balance ;	// the data to be protected
	};

	CDataPool	*theDataPool ;  // a datapool containing the data to be protected double balance; 
	CMutex	    *theMutex;	       // a pointer to a hidden mutex protecting the ‘Balance’ variable above
	theData		*D_ptr ;			// pointer to the data

public:
	BOOL WithdrawFunds (double amount) { 
		 theMutex -> Wait() ;
		BOOL Status = FALSE ;
		if (D_ptr->Balance >= amount) 	{
		        Status = TRUE ;
		        D_ptr->Balance = D_ptr->Balance - amount ;	}
		 theMutex -> Signal() ;
		return Status ;
	}
	void DepositFunds (double amount) {
		theMutex -> Wait() ;
		D_ptr->Balance = D_ptr->Balance + amount ;
		theMutex -> Signal() ;
	} 

	double GetBalance() { 
		theMutex->Wait() ;
		return D_ptr->Balance ; 
		theMutex->Signal() ;
	}
	
	void SetBalance(double newBalance) { 
		theMutex->Wait() ;
		D_ptr->Balance = newBalance; 
		theMutex->Signal() ;
	}

	// constructor and destructor
	 BankAccount (string Name) { 
		 theMutex = new CMutex(string("__Mutex__") + string(Name));
		 theDataPool = new CDataPool(string("__DataPool__") + string(Name), sizeof(struct theData));
		 D_ptr = (struct theData *)(theDataPool->LinkDataPool()); 
	 }
	~BankAccount () { /* delete mutex and datapool; */ }
} ;	
#endif