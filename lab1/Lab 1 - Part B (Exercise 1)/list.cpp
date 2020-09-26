#include "list.h"

//Default constructor
list::list(){
    ptr = NULL;
}

//Default destructor
list::~list(){
    Node* temp = NULL;
    while(ptr != NULL){
        if (next != NULL)
            temp = next;
        delete ptr;
        ptr = temp;
    }
    
}

void list::insert(int val){
    Node temp = new Node(val);
    Node* temp_ptr = ptr;
    if (ptr == NULL)
        ptr = temp;
    else{
        while (temp_ptr->next != NULL){
            temp_ptr = temp_ptr->next;
        }
        temp_ptr->next = temp;
    }
}

void list::Delete(){
    Node* temp_ptr = ptr;
    Node* prev_ptr;
    while (temp_ptr->next != NULL){
        prev_ptr = temp_ptr;
        temp_ptr = temp_ptr->next;
        if (temp_ptr->next == NULL)
            prev_ptr->next == NULL;
    }
    delete temp_ptr;
}

int list::get(int i){
    Node* temp_ptr = ptr;
    if (i == 1)
        return ptr->value;
    for (count = 1; count != i; ++count){
        if (temp_ptr->next != NULL){
            temp_ptr = temp_ptr->next;
        }
        else{ //item does not exist
            return 0;
        }
    }
    return temp_ptr->value;
}