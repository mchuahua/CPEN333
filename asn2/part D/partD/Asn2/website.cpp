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
student* website::getNextPromo(int studentnum) {
	if (studentnum == 0){
		cout << "Next promotion consideration is for student 1" << endl;
		return theStudent;
	}
	else if (studentnum == 1){
		cout << "Next promotion consideration is for student 2" << endl;
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

// Called by advisor 
student* website::getNextStudentForGraduation(int studentnum) {
	if (studentnum == 0){
		if (theStudent->grad_req) {
			cout << "Next graduation consideration is for student 1" << endl;
			return theStudent;
		}
	}
	else if (studentnum == 1){
		if (theStudent2->grad_req) {
			cout << "Next graduation consideration is for student 2" << endl;
			return theStudent2;
		}
	}
	else {
		cout << "Website error: student not found!" << endl;
	}
	return NULL;
}

void website::DoGradReq(student* guy) {
	guy->grad_req = true;
}


student* website::viewNextIncident(int studentnum){
	if (studentnum == 0){
		cout << "Next incident consideration is for student 1" << endl;
		//cout << theStudent->name << endl;
		return theStudent;
	}
	else if (studentnum == 1){
		cout << "Next incident consideration is for student 2" << endl;
		return theStudent2;
	}
	else {
		cout << "Website error: student not found!" << endl;
	}
	return NULL;
}

void website::notifyProfessor(student* guy){
	theProfessor->courseGradeToZero(guy);
}

void website::notifyDean(student* name, int decision){
	theDean->UpdateRecords(name, decision);
}

void website::updateGrade(student* guy, int grade){
	guy->course_grade = grade;
}

