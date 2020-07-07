#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include <vector>
#include "Vertex.h"

using namespace std;

class Stack
{
public:
    Stack(); //Constructor
    bool isEmpty(); //Check if the stack is empty
    void push(Vertex n); //Push item "n" into the stack
    void pop(); //Pop the top item of the stack
    Vertex peek(); //Return the top item of the stack
private:
    vector<Vertex> myStack;
};

#endif // STACK_H_INCLUDED
