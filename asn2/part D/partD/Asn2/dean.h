#pragma once
#include <string>
#include "student.h"

using namespace std;

// Forward declaration to prevent circular instantiation, which happens even with the #pragmaonce and #ifndef definitions.
class website;

class dean
{
    string name;
public:
    website *theWebsite;
    string recordbook;

    dean(string name);
    ~dean();
    void UpdateRecords(student* guy, int decision);
};

