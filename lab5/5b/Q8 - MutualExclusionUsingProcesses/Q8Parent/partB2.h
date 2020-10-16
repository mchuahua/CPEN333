#pragma once
#include "..\..\..\..\RTExamples\rt.h"


class partB2 : public ActiveClass
{
public:
	partB2();
	~partB2();
	int __thiscall Child1(void *args);
	int __thiscall Child2(void *args);
	int __thiscall Child3(void *args);

private:
	int main();
	//UINT __stdcall Child(void *args);
	CMutex *theMutex;

};

