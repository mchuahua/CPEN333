#include "student.h"

student::student(){

}

student::~student(){
    
}

void student::ViewForm() {
    cout << "Viewing form: ";
    for (int i = 0; i < 3; i++){
        cout << form[i] << " ";
    }
    cout << endl;
}

void student::EditForm(int arr[3]) {
    theWebsite->UpdateForm(this, arr);
}

void student::ReqGrad() {

}