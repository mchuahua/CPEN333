#pragma once
#ifndef __WEBSITE__
#define __WEBSITE__
#include <string>
#include <list>
#include "student.h"
#include "president.h"
#include "advisor.h"
#include "professor.h"
#include "dean.h"
#include <iostream>

using namespace std;

class website
{

public:
    string name;

    // Pointers
    student* theStudent;
    student* theStudent2;
    president* thePresident;
    advisor* theAdvisor;
    professor* theProfessor;
    dean* theDean;
    int studentnum = 2;
    int formviewed_test = 0;
    
    // Constructors and descructers
    website();
    ~website();
    void viewForm(student* guy);
    void updateForm(student *guy,int arr[2]);
    student* getNextForm(int studentnum);
    void updatePlacement(student* guy, string program);
    student* getNextPromo(int studentnum);
    student* viewNextIncident(int studentnum);
    student* getNextStudentForGraduation(int studentnum);
    void DoGradReq(student* guy);
    void notifyProfessor(student* guy);
    void notifyDean(student* guy , int decision);
    void updateGrade(student* guy, int grade);
    
    
    //Add pointer links
    void AddStudent(student* asdf) { theStudent = asdf; asdf->theWebsite = this; };
    void AddStudent2(student* asdf) { theStudent2 = asdf; asdf->theWebsite = this; };
    void AddPresident(president* asdf) { thePresident = asdf; thePresident->theWebsite = this; };
    void AddAdvisor(advisor* asdf) { theAdvisor = asdf; theAdvisor->theWebsite = this; };
    void AddProfessor(professor* asdf) { theProfessor = asdf; theProfessor->theWebsite = this; };
    void AddDean(dean* asdf) { theDean = asdf; theDean->theWebsite = this; };
};
#endif