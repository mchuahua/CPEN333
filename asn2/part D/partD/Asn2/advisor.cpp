#include "advisor.h"
#include "website.h"
#include <iostream>


advisor::advisor(string asdf){
    name = asdf;
    cout << name << " advisor initialized." << endl;
}

advisor::~advisor(){
    delete theWebsite;
}

bool advisor::ProcessGrad(){
    return 0;
}

int advisor::ProcessPromo(){
    return 0;
}

// Advisor chooses 
void advisor::ProcessPlacement(){
    string program;
    for (int i = 0; i < 2; i++) {
        student* temp = theWebsite->getNextForm(i);
        if (temp == NULL){
            cout << "Advisor sees no more students for processing placement." << endl;
        }
            // Algo. Basically give them their top choice if above 80. Otherwise give them their second choice.
        if (temp->avg > 80){
            if (temp->form == NULL){
                cout << "Form is not filled; advisor will default set a program to FIZZ" << endl;
                program = "FIZZ";
            }
            if (temp->form[0] == 1)
                program = "ELEC";
            else if (temp->form[0] == 2)
                program = "FIZZ";
            else{
                program = "FIZZ";
            }
        }
        else
            program = "FIZZ";
        theWebsite->updatePlacement(temp, program);
    }
    cout << "Advisor is done processing placements." << endl;
}