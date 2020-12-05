#pragma once
#ifndef __advisor__
#define __advisor__

#include <string>
#include "student.h"
using namespace std;

// Forward declaration to prevent circular instantiation, which happens even with the #pragmaonce and #ifndef definitions.
class website;

class advisor
{

public:
    string name;

    website* theWebsite;
    advisor(string asdf);
    ~advisor();

    void ProcessGrad();
    void ProcessPromo();
    void ProcessPlacement();
};



#endif // !__advisor__


