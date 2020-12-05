#include <stdio.h>
#include <string>
#include "website.h"
#include <iostream>

using namespace std;

int main(){
    website* theWebsite = new website();
    student* student1 = new student("Martin", 0, 1, 85, 82, false);
    student* student2 = new student("Varun", 1, 1, 60, 70, true);
    advisor* enggadv = new advisor("Cathleen");
    president* pres = new president("Keanu Reeves");
    professor* prof = new professor("Paul Davies", "CPEN333");
    dean* enggdean = new dean("Michael Jackson");

// Link them together
    theWebsite->AddStudent(student1);
    theWebsite->AddStudent2(student2);
    theWebsite->AddAdvisor(enggadv);
    theWebsite->AddDean(enggdean);
    theWebsite->AddPresident(pres);
    theWebsite->AddProfessor(prof);

    int temp_form1[2] = { 1, 2 };
    int temp_form2[2] = { 2, 1 };

// Part 2: First year program application
    student1->ViewForm();
    student1->EditForm(temp_form1);
    student1->ViewForm();

    student2->ViewForm();
    student2->EditForm(temp_form2);
    student2->ViewForm();
    enggadv->ProcessPlacement();

// Part 6: 2nd+ year promotion
    cout << "\nAdvisor requests for Promotion task" << endl;
    enggadv->ProcessPromo();

// Part 7: Graduation
    student2->year = 4;
    student1->year = 4;
    student2->outstanding_fees = true;
    student1->complimentary_course_comp = false;
    student2->ReqGrad();
    student1->ReqGrad();
    cout << "\nAdvisor requests for Graduations task" << endl;

    enggadv->ProcessGrad();

    //let them grad
    student2->outstanding_fees = false;
    student1->complimentary_course_comp = true;
    student2->ReqGrad();
    student1->ReqGrad();
    cout << "\nAdvisor requests for Graduations task" << endl;
    enggadv->ProcessGrad();

// Part 8: Cheating
    cout << student1->name << endl;
    cout << student2->name << endl;
    student2->cheating_incidents = 1;
    student1->cheating_incidents = 3;
    //TODO: Insert presidents thing here
    cout << "President requests for Cheating accusations task" << endl;
    
    pres->processIncidents();
    
}