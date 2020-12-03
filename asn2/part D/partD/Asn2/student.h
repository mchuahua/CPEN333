#pragma once
#include <string>
#include <iostream>
using namespace std;

class student
{
    string name;

public:
    student();
    ~student();
    int id;
    int form[3];
    int program;
    int year;
    int year_completion;
    website *theWebsite;
    
    void ViewForm();
    void EditForm();
    void ReqGrad();
};

