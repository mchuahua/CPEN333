#pragma once
#include <string>
using namespace std;

class advisor
{
    string name;
    public:
    advisor();
    ~advisor();

	bool ProcessGrad();
	int ProcessPromo();
	int ProcessPlacement();
    website *theWebsite;

};

