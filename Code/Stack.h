#ifndef STACK_H
#define STACK_H

#include <iostream>
#include "Calculator.h"

using namespace std;

#define stack_size 30         // stack_size is defined for the size of the stack

template <class T>
class Stack
{
    public:
        Stack();
        ~Stack();
        bool pop();
        bool push(T);
        bool is_empty();
        bool is_full();
        int get_size();
        T get_top();

    private:
        T *list;
        int count, top;
};

#endif // STACK_H
