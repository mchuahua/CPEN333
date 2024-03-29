#include "dean.h"
#include "website.h"
#include <iostream>

// Constructor
dean::dean(string name1){
    name = name1;
}

// Gotta delete dynamically allocated pointer
dean::~dean(){
    delete theWebsite;
}

// Called by website.
void dean::UpdateRecords(student* guy, int decision) {
    string outcome;
    if (decision == 1) {
        outcome = "Suspended for 1 term";
    }
    else if (decision == 2) {
        outcome = "Suspended for 2 terms";
    }
    else if (decision == 3) {
        outcome = "Expelled";
    }

    string note = guy->name + " with id#" + to_string(guy->id) +" "+ outcome +"\n";
    cout << "Dean updated record with: " << note;
    recordbook += note;
}