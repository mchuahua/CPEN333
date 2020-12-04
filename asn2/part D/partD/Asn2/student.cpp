#include "student.h"
#include "website.h"
// Initalized by main
student::student(string name_, int id_, int year_, int comp_, int avg_){
    name = name_;
    avg = avg_;
    id = id_;
    year = year_;
    year_completion = comp_;

    cout << "~~~~~~~~~Initializing student~~~~~~~~~~" << endl;
    cout << "Student name is " << name << endl;
    cout << "Student avg is " << avg << endl;
    cout << "Student id is " << id << endl;
    cout << "Student year is " << year << endl;
    cout << "Student year completed " << year_completion << endl;
    cout << "~~~~~~Done initializing student~~~~~~~~" << endl;
}

student::~student(){
    delete theWebsite;
}

// Called by main
void student::ViewForm() {
    theWebsite->viewForm(this);
}

// Called by main
void student::EditForm(int arr[2]) {
    theWebsite->updateForm(this, arr);
}

// Called by main
//void student::ReqGrad() {
//    theWebsite->getGradReq(this);
//}