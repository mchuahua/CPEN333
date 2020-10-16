#pragma once
#include "..\..\..\..\RTExamples\rt.h"
#include <string>

class partC : public ActiveClass
{
public:
	partC(string name);
	~partC();
	int __thiscall Child1(void *args);
	int __thiscall Child2(void *args);
	int __thiscall Child3(void *args);

private:
	void WriteToScreen(int x, int y, string input);
	//UINT __stdcall Child(void *args);
	CMutex *theMutex;
	int main();
};

