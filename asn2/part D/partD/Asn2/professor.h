#pragma once
#ifndef __professor__
#define __professor__

#include <string>
#include "student.h"
using namespace std;

class website;

class professor
{
    string name;
    string coursename;
    
public:
    website* theWebsite;
    professor(string name, string coursename);
    ~professor();
    void courseGradeToZero(student* name);

};



#endif // !__professor__



