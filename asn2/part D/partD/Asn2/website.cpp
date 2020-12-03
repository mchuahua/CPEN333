#include "website.h"

website::website(){

}

website::~website(){

}


void website::updateForm(student* guy, int arr[3]) {
	if (guy->year != 1) return;
	for (int i = 0; i < 4; i++) {
		guy->form[i] = arr[i];
	}
}

void website::getNextForm() {

}

void website::updatePlacement() {

}

void website::display() {

}

list<student*> website::getStudents(){
    return studentList;
}