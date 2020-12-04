#pragma once
#include <string>
#include "student.h"

using namespace std;

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

