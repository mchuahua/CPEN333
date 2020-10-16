#pragma once
#include "..\..\..\..\RTExamples\rt.h"
#include <atomic>

class partB1 : public ActiveClass
{
public:
	partB1();
	~partB1();
	int __thiscall Child1(void *args);
	int __thiscall Child2(void *args);
	int __thiscall Child3(void *args);

private:
	int main();
	//UINT __stdcall Child(void *args);
	atomic_flag atomicflag;

};

