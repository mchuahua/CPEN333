#include "website.h"


website::website(){
	name = "SSC";
	cout << name << " website initiated." << endl;
}

website::~website(){
    delete theStudent;
    delete thePresident;
    delete theAdvisor;
    delete theProfessor;
    delete theDean;
}

// Called by student to update form
void website::updateForm(student* guy, int arr[2]) {
	if (guy == NULL || arr == NULL){
		cout << "Error no student found" << endl;
		return;
	}
	if (guy->year != 1) return;
	for (int i = 0; i < 4; i++) {
		guy->form[i] = arr[i];
	}
}

// Called by student to print to display
void website::viewForm(student* guy){
	if (guy == NULL){
		cout << "Error no student found" << endl;
		return;
	}
	cout << "Viewing form: ";
    for (int i = 0; i < 2; i++){
        cout << guy->form[i] << " ";
    }
    cout << endl;
}

// Called by advisor 
student* website::getNextForm(int studentnum) {
	if (studentnum == 0){
		cout << "Next form is student 1" << endl;
		return theStudent;
	}
	else if (studentnum == 1){
		cout << "Next form is student 2" << endl;
		return theStudent2;
	}
	else {
		cout << "Website error: student not found!" << endl;
	}
	return NULL;
}

// Called by advisor
void website::updatePlacement(student* guy, string program) {
	if (guy == NULL){
		cout << "Error no student found" << endl;
		return;
	}
    guy->program = program;
    cout << "Website updated with " << guy->id << " placed in program: " << guy->program << endl;
}