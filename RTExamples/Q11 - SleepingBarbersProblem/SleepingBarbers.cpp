#include "..\rt.h"

///////////////////////////////////////////////////////////////////////////////
//	Example of the Sleeping Barbers Problem
///////////////////////////////////////////////////////////////////////////////

CSleepingBarbers b1("JimsBarberShop", 2) ;		// two chairs in barber shop waiting room, minimum is 1 otherwise everyone leaves in disgust

//
// This thread represent a customer
//

class Customer : public ActiveClass
{
public:	Customer() {}					// constructor doesn't need to do anything in this example	

private:
	int main(void)
	{
		for(int i = 0; i < 10; i ++)			// get 10 haircuts over a suitable long time period
		{
			cout << "Customer Arriving.....\n";
	
			if(b1.CustomerWaitsForBarber() == FALSE)	{		// if FALSE returned then I left in disgust
				//TEXT_COLOUR(12, 15) ;
				cout << "Not Enough Chairs....Left in Disgust\n";
				//TEXT_COLOUR(15, 0) ;
			}
	
			SLEEP(3000) ;						// allow hair to grow again (3 Seconds) !!!!
		}	
		return 0 ;								// terminate thread
	}
};

//
// This thread represent a Barber
//

class Barber : public ActiveClass
{
public:	Barber() {}					// constructor doesn't need to do anything in this example	UINT __stdcall Barber(void *args)	

	int main(void)
	{
		while(1)	{
			b1.BarberWaitsForCustomer() ;		// wait for my next customer
			cout << ".....Serving Customer.....\n";
			SLEEP(1500) ;						// simulate time for cutting hair = 1.5mSec
		}
		return 0 ;							// terminate thread
	}
};

int main()
{
	const int NumBarbers = 2;
	const int NumCustomers = 10 ;

	Barber theBarbers[NumBarbers] ;			// an array of 2 barbers all suspended
	Customer theCustomers[NumCustomers];		// an array of 10 customers all suspended

	//	create 9 customers with suitable delays in between to simulate the random arrival of customers
	// 1st three customer arrive as soon as the barbers shop opens

	theBarbers[0].Resume() ;
	theBarbers[1].Resume() ;
	
	theCustomers[0].Resume() ;
	theCustomers[1].Resume() ;
	theCustomers[2].Resume() ;
	theCustomers[3].Resume() ;

	SLEEP(1000) ;

	theCustomers[4].Resume() ;
	theCustomers[5].Resume() ;

	// then a rush of 4 customer after work closes
	SLEEP(1000) ;
	theCustomers[6].Resume() ;
	theCustomers[7].Resume() ;
	theCustomers[8].Resume() ;
	theCustomers[9].Resume() ;


	for(int i = 0; i < NumCustomers; i ++)
		theCustomers[i].WaitForThread() ;

	theBarbers[0].WaitForThread() ;
	theBarbers[1].WaitForThread() ;

	
	return 0 ;
}
