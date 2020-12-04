#pragma once
#ifndef __advisor__
#define __advisor__

#include <string>
#include "student.h"
using namespace std;

class website;

class advisor
{
    string name;

public:
    website* theWebsite;
    advisor(string asdf);
    ~advisor();

    void ProcessGrad();
    void ProcessPromo();
    void ProcessPlacement();
};



#endif // !__advisor__


