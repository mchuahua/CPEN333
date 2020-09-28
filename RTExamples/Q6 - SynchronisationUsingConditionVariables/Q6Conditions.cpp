//
//	Pedestrian crossing simulation
//

#include "..\rt.h"				

CCondition   SafeToCross("SafeToCross") ;  		// create a non-signalled condition
CCondition   SafeToDrive("SafeToDrive") ;  		// create a non-signalled condition

//
//	A thread to simulate a Pedestrian
//
	
UINT __stdcall Pedestrian(void   *args)						// thread to represent pedestrian
{
	int MyPedestrianNumber = *(int *)(args) ;				// get my number given to me during creation

	while(1)	{											// do forever
		SLEEP(600 * MyPedestrianNumber) ;					// sleep for a random time period
		SafeToCross.Wait() ;								// wait for green man
		cout << "P" << MyPedestrianNumber;					// show that I have crossed
	}								
	return 0 ;
}

//
//	A thread to simulate a Car
//

UINT __stdcall Car(void    *args)
{
	int MyCarNumber = *(int *)(args) ;						// get my number given to me during creation

	while(1)	{											// do forever
		SLEEP(300 * MyCarNumber) ;							// sleep for a random time period
		SafeToDrive.Wait() ;								// wait for green light to give permission to drive over crossing
		cout << "C" << MyCarNumber;						// show I have driven over
	}								
	return 0 ;
}

//
//	The main() thread simulates the traffic light controller
//

int main()
{
	CThread		*ThePedestrians[10] ;		// 10 pedestrians
	CThread		*TheCars[10] ;				// 10 cars wizzing up and down road doing handbrake turns (as you do)

	int			i ;
	int			PedestrianNumber[] = { 1,2,3,4,5,6,7,8,9,10} ;
	int			CarNumber[] = { 1,2,3,4,5,6,7,8,9,10} ;

	for(i = 0; i < 10; i++)
		ThePedestrians[i] = new CThread(Pedestrian, ACTIVE, &PedestrianNumber[i]) ;

	for(i = 0; i < 10; i++)
		TheCars[i] = new CThread(Car, ACTIVE, &CarNumber[i]) ;


	while(1)	{					
		SafeToCross.Reset();		// stop pedestrians
		SLEEP(2000) ;				// wait a suitable time delay between lights changing
		SafeToDrive.Signal() ;		// allow cars to drive over pedestrian crossing
		SLEEP(10000) ;				// allow cars to drive for 10 seconds
		SafeToDrive.Reset();		// stop cars
		SLEEP(2000) ;				// wait a suitable time delay between lights changing
		SafeToCross.Signal() ;		// allow pedestrians to cross
		SLEEP(15000) ;				// allow pedestrians to cross for 15 seconds
	}
	
	return 0 ;
}
