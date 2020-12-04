#include <stdio.h>
#include <string>
#include "website.h"
#include <iostream>

using namespace std;

int main(){
    website* theWebsite = new website();
    student* student1 = new student("s1", 0, 1, 85, 82);
    student* student2 = new student("s2", 1, 1, 90, 70);
    advisor* enggadv = new advisor("Cathleen");

    theWebsite->AddStudent(student1);
    theWebsite->AddStudent2(student2);
    theWebsite->AddAdvisor(enggadv);

    int temp_form1[2] = { 1, 2 };
    int temp_form2[2] = { 2, 1 };
    student1->ViewForm();
    student1->EditForm(temp_form1);
    student1->ViewForm();

    student2->ViewForm();
    student2->EditForm(temp_form2);
    student2->ViewForm();

    enggadv->ProcessPlacement();
}