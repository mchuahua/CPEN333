#include "professor.h"
#include "website.h"

#include <iostream>

// Giving the professor a nice name
professor::professor(string name_, string course_name){
    name = name_;
    coursename = course_name;
    cout << "A very good professor named " << name << " is teaching the course " << coursename << endl;
}

// Gotta delete the website
professor::~professor(){
    delete theWebsite;
}

// Called by website
void professor::courseGradeToZero(student* name){
    theWebsite->updateGrade(name, 0);
}