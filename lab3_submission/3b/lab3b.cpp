// lab3b.cpp : Defines the entry point for the console application.
//

#include "WashingMachine.h"
#include "CoffeeMaker.h"


int main()
{
	//Create 5 instances each
	WashingMachine WM1(1), WM2(2), WM3(3), WM4(4), WM5(5);
	CoffeeMaker CM1(1), CM2(2), CM3(3), CM4(4), CM5(5);

	WM1.Resume();
	WM2.Resume();
	WM3.Resume();
	WM4.Resume();
	WM5.Resume();

	CM1.Resume();
	CM2.Resume();
	CM3.Resume();
	CM4.Resume();
	CM5.Resume();

	CM1.Stop();
	WM1.Stop();
	CM2.Stop();
	WM2.Stop();
	CM3.Stop();

	Sleep(13000);

	CM1.Start();
	WM1.Start();
	CM2.Start();
	WM2.Start();
	CM3.Start();

	WM3.Stop();
	WM4.Stop();
	WM5.Stop();
	CM4.Stop();
	CM5.Stop();

	Sleep(13000);

	WM3.Start();
	WM4.Start();
	WM5.Start();
	CM4.Start();
	CM5.Start();


	WM1.WaitForThread();
	WM2.WaitForThread();
	WM3.WaitForThread();
	WM4.WaitForThread();
	WM5.WaitForThread();

	CM1.WaitForThread();
	CM2.WaitForThread();
	CM3.WaitForThread();
	CM4.WaitForThread();
	CM5.WaitForThread();


	return 0;
}

