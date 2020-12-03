#pragma once

#include <string>
#include <list>
#include "student.h"
#include "president.h"
#include "advisor.h"
#include "professor.h"
#include "dean.h"

using namespace std;

class website
{


    public:
    // Constructors and descructers
    website();
    ~website();
    
    string name;

    void updateForm(student *guy,int arr[3]);
    void getNextForm();
    void updatePlacement();
    void getGradReq();
    list<student*> getStudents();
    void getIncident();
    void decisionOutcome();
    void display();

    // Pointers
    student *theStudent;
    list <student*> studentList;
    president *thePresident;
    advisor *theAdvisor;
    professor *theProfessor;
    dean *theDean;
    
    //Add things
    void AddStudent(student *asdf){studentlist.push_back(asdf); asdf -> theWebsite = this;}
    void AddPresident(president *asdf){thePresident = asdf; thePresident -> theWebsite = this;}
    void AddAdvisor(advisor *asdf){theAdvisor = asdf; theAdvisor -> theWebsite = this;}
    void AddProfessor(professor *asdf){theProfessor = asdf; theProfessor -> theWebsite = this;}
    void AddDean(dean *asdf){theDean = asdf; theDean -> theWebsite = this;}

};

