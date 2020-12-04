#pragma once
#ifndef __professor__
#define __professor__

#include <string>
using namespace std;
class website;

class professor
{
    string name;
public:
    website* theWebsite;

    professor();
    ~professor();


};



#endif // !__professor__



