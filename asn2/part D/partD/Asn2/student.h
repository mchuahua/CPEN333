#pragma once
#ifndef __STUDENT__
#define __STUDENT__
#include <string>
#include <iostream>
using namespace std;

class website;

class student
{
    string name;

public:
    
    int id;
    int form[3];
    string program;
    int avg;
    int year;
    int year_completion;
    website* theWebsite;
    
    student(string name, int id, int year, int comp, int avg);
    ~student();

    void ViewForm();
    void EditForm(int arr[3]);
    void ReqGrad();
};

#endif