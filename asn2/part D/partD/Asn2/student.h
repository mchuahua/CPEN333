#pragma once
#ifndef __STUDENT__
#define __STUDENT__
#include <string>
#include <iostream>
using namespace std;

class website;

class student
{

public:
    string name;

    int id;
    int form[3];
    string program;
    int avg;
    int year;
    int year_completion;
    bool graduation_eligible = false;
    bool grad_req = false;
    bool outstanding_fees;
    int cheating_incidents = 0;
    int terms_blocked = 0;
    bool registration_blocked = false;
    int course_grade = 69;
    bool complimentary_course_comp = true;
    website* theWebsite;
    
    student(string name, int id, int year, int comp, int avg, bool outfees);
    ~student();

    void ViewForm();
    void EditForm(int arr[3]);
    void ReqGrad();
};

#endif