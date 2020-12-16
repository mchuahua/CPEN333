#include "advisor.h"
#include "website.h"
#include <iostream>

// Constructor. Copies the input string to the name variable inside the class.
advisor::advisor(string asdf){
    name = asdf;
    cout << name << " advisor initialized." << endl;
}

// Destructor. Deletes the website pointer which is dynamically allocated.
advisor::~advisor(){
    delete theWebsite;
}

// Called by main.
void advisor::ProcessGrad(){
    for (int i = 0; i < 2; i++) {
        student* temp = theWebsite->getNextStudentForGraduation(i);
        if (temp == NULL){
            cout << "Advisor sees no more students for processing grad." << endl;
            return;
        }
        // Algorithm. Basically promote if completion > 80. Otherwise hell naw. Definitely not a biased advisor.
        if (temp->grad_req && !temp->outstanding_fees && temp->complimentary_course_comp){
            cout << "Nice. Graduated student " << temp->name << endl;
        }
        else if (temp->outstanding_fees || !temp->complimentary_course_comp){
            if (temp->outstanding_fees) {
                cout << "lol u thought u could get away from paying fees..." << temp->name << endl;
                temp->grad_req = false;
            }
            else{
                cout << "lol u thought u could get away from doing apsc 450..." << temp->name << endl;
                temp->grad_req = false;
            }
        }
        else {
            cout << "Student " << temp->name << " is not eligible for grad! You need to suffer more!" << endl;
        }
    }
    cout << "Advisor is done processing graduation for students." << endl;
}

// Called by main.
void advisor::ProcessPromo(){
    // Get next student info 
    for (int i = 0; i < 2; i++) {
        student* temp = theWebsite->getNextPromo(i);
        if (temp == NULL){
            cout << "Advisor sees no more students for processing promo." << endl;
            return;
        }
        // Algo. Basically promote if completion > 80. Otherwise hell naw
        if (temp->year_completion < 0){
            cout << "Wait what, how is there a negative course completed" << endl;
        }
        else if (temp->year_completion > 80){
            temp->year++;
            cout << "Student year updated to " << temp->year << endl;
        }
    }
    cout << "Advisor is done processing promos." << endl;
}

// Advisor chooses. Called by main.
void advisor::ProcessPlacement(){
    string elec = "ELEC";
    string fizz = "FIZZ";
    string program;
    for (int i = 0; i < 2; i++) {
        student* temp = theWebsite->getNextForm(i);
        if (temp == NULL){
            cout << "Advisor sees no more students for processing placement." << endl;
            return;
        }
            // Algo. Basically give them their top choice if above 80. Otherwise give them their second choice.
        if (temp->avg > 80){
            if (temp->form == NULL){
                cout << "Form is not filled; advisor will default set a program to FIZZ" << endl;
                program = fizz;
            }
            if (temp->form[0] == 1)
                program = elec;
            else if (temp->form[0] == 2)
                program = fizz;
            else{
                program = fizz;
            }
        }
        else
            program = fizz;
        theWebsite->updatePlacement(temp, program);
    }
    cout << "Advisor is done processing placements." << endl;
}