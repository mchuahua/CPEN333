#pragma once
#ifndef __PRESIDENT__
#define __PRESIDENT__
#include <string>

using namespace std;
// Forward declaration to prevent circular instantiation, which happens even with the #pragmaonce and #ifndef definitions.
class website;

class president
{
public:
    string name;
    website *theWebsite;

    president(string name);
    ~president();
    void processIncidents();
};


#endif