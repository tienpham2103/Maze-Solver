#include "Stack.h"

Stack::Stack(){
    //Constructor is empty
}

bool Stack::isEmpty(){
    return myStack.empty();
}

void Stack::push(Vertex n){
    myStack.push_back(n);
}

void Stack::pop(){
    if (!isEmpty())
        myStack.pop_back();
}

Vertex Stack::peek(){
    if (!isEmpty())
        return myStack.back();
}
