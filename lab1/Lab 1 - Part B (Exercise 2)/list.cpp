#include "list.h"
#include <iostream>
//Default constructor
list::list(){
    ptr = NULL;
}

//Default destructor
list::~list(){
    T* temp = NULL;
    while(ptr != NULL){
        if (next != NULL)
            temp = next;
        delete ptr;
        ptr = temp;
    }
    
}

template <class T>
void list<T>::insert(T val){
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

template <class T>
void list<T>::Delete(){
    Node* temp_ptr = ptr;
    while (temp_ptr->next != NULL)
        temp_ptr = temp_ptr->next;
    delete temp_ptr;
}

template <class T>
T list<T>::get(int i){
    T* temp_ptr = ptr;
    if (i == 1)
        return ptr->value;
    for (count = 1; count != i; ++count){
        if (temp_ptr->next != NULL){
            temp_ptr = temp_ptr->next;
        }
        else{ //item does not exist
            std::cout <<"error item does not exist" << std::endl;
        }
    }
    return temp_ptr->value;
}