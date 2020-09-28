#include "../../rt.h"

class 	BankAccount   {
private:
	struct theDataInTheMonitor {	// describe the data to be stored in this monitor
		double	Balance ;	// the data to be protected, in this example a simple ‘float’, 
	} ;

	CDataPool *theMonitorDataPool ;

	struct theDataInTheMonitor *PointerToTheDataInTheMonitor ;

	CMutex	*theMutex;	// a pointer to a hidden mutex protecting the ‘Balance’ variable above

public:
	BOOL Withdraw (double amount) { 
		theMutex -> Wait() ;
		BOOL Status = FALSE ;
		if (PointerToTheDataInTheMonitor-> Balance >= amount) 	{
		        Status = TRUE ;
		        PointerToTheDataInTheMonitor->Balance = PointerToTheDataInTheMonitor->Balance - amount ;	
		}
		theMutex ->Signal() ;
		return Status ;
	} 

	void Deposit (double amount){
		theMutex ->Wait() ;
		PointerToTheDataInTheMonitor->Balance = PointerToTheDataInTheMonitor->Balance + amount ;
		theMutex ->Signal() ;
	} 
	
	double GetBalance() {
		double theBalance ;
		theMutex ->Wait() ;
		theBalance = PointerToTheDataInTheMonitor->Balance ;
		theMutex->Signal() ;
		return theBalance ;
	}

	// constructor and destructor

	 BankAccount (string theName) { 
		theMutex = new CMutex ("__MonitorMutex__" + theName) ; 
		theMonitorDataPool = new CDataPool("__MonitorDataPool__" + theName, sizeof(struct theDataInTheMonitor)) ;
		PointerToTheDataInTheMonitor = (struct theDataInTheMonitor *)(theMonitorDataPool->LinkDataPool()) ;
		
		PointerToTheDataInTheMonitor->Balance = 0.0 ; 
	}

	~ BankAccount () { 
		delete theMutex; 
		delete theMonitorDataPool;
	}
} ;	
