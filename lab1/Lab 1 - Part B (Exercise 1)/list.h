#pragma once

#ifndef __list__
#define __list__


//Node class w/ int value
class Node 
{
public:
    Node(int val){value = val;}
    ~Node(){}
    void setVal(int val){value = val;}
    int getVal(){return value;}
    Node* next(){return next;}
    Node* prev(){return prev;}
private:
    Node* prev;
    Node* next;
    int value;
};


//list class
class list
{
public:
    List();
    ~List();
    void insert(int val);
    void Delete(int node);
    int get(int i);
private:
    Node *ptr; // pointer to 1st node in list
};




#endif