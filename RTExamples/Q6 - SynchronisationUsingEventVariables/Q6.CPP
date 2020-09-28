#include <stdio.h>		
#include "..\rt.h"				// change pathlist to rt.h to suit location on disk

CEvent   ChassisReady("ChassisInPosition") ;  		// create a non-signalled event
CEvent   RobotFinished("RobotDone") ;  				// create a non-signalled event

	
class ProductionLine : public ActiveClass
{
public:
	int main()
	{
		while(1)	{				// do forever
			cout << "Production Line: New Chassis Arrived\n" ;
			ChassisReady.Signal() ;	// signal event occurrence
			RobotFinished.Wait() ;	// wait for robot to assemble car
			SLEEP(2500) ;			// delay while a new chassis is brought into place
			cout << "Production Line: Waiting for next chassis\n";
			SLEEP(2500) ;
		}								
		return 0 ;
	}
} ;

class Robot : public ActiveClass
{
public:
	int main()
	{
		while(1)	{					// do forever
			cout << "Robot: Waiting for Next Chassis\n";
			ChassisReady.Wait() ;		// wait for next chassis to arrive
			cout << "Robot: Assembling Chassis\n";
			SLEEP(4000) ;				// delay while we assemble car
			cout << "Robot: Finished Assembly\n";
			RobotFinished.Signal() ;	// signal robot has assembled car
		}								
		return 0 ;
	}
};

int main()
{
	Robot 	TheRobot ;				    // create an active child thread
	TheRobot.Resume() ;

	SLEEP(500) ;						// let the robot get up and running

	ProductionLine 	TheProductionLine ;	// create an active child thread
	TheProductionLine.Resume() ;


	TheRobot.WaitForThread() ;
	TheProductionLine.WaitForThread() ;
	return 0 ;
}
