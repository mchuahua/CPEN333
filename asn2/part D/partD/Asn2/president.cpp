#include "president.h"
#include "website.h"
#include "student.h"
#include <iostream>

// Naming the president to a nice name
president::president(string name1){
    name = name1;
}

// Gotta delte the webiste
president::~president(){
    delete theWebsite;
}

// Called by main
void president::processIncidents(){
    // Get next student info 
    for (int i = 0; i < 2; i++) {
        student* temp = theWebsite->viewNextIncident(i);
        if (temp == NULL){
            cout << "President's Office sees no more students for potential incidents." << endl;
            return;
        }
        // Algo. Basically suspend if 0<x<3. Otherwise EXPULSION
        if (temp->cheating_incidents < 3 && temp->cheating_incidents > 0){
            cout << "SUSPENSION for student " << temp->name << endl;
            theWebsite->notifyDean(temp, temp->cheating_incidents);
            theWebsite->notifyProfessor(temp);
            temp->registration_blocked = true;
        }
        else if (temp->cheating_incidents >=3 ){
            cout << "EXPULSION for student " << temp->name << endl;
            theWebsite->notifyDean(temp, temp->cheating_incidents);
            theWebsite->notifyProfessor(temp);   
            temp->registration_blocked = true;     
        }
        else
            cout << "Student " << temp->name << " is ok, no incident very good" << endl;
    }
    cout << "President's Office is done processing incidents." << endl;
}



