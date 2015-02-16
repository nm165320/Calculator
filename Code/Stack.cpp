// Stack.cpp FUNCTION DEFINITION
#include "Stack.h"

/**
#Constructor# ======================================================================
; Name...........: Stack()
; Description....: Constructor that will initialize private data members to a null
;                  state.
; Syntax.........: Automatically run when a object with a parameter is created.
; Parameters.....: NONE
; =================================================================================*/
template <class T>
Stack<T>::Stack()
{
    list = new T[stack_size];
    count = 0;
    top = -1;
}

/**
#Destructor# ======================================================================
; Name...........: ~Stack()
; Description....: Destructor that will free any dynamically allocated memory.
; Syntax.........: Automatically run when the program is done running.
; Parameters.....: NONE
; =================================================================================*/
template <class T>
Stack<T>::~Stack()
{
    delete [] list;
}

/**
#FUNCTION# =========================================================================
; Name...........: bool pop()
; Description....: Function that will remove the top data variable from the stack
;                  and decrease the stack by one.
; Syntax.........: object_name.pop()
; Parameters.....: NONE
; =================================================================================*/
template <class T>
bool Stack<T>::pop()
{

    if(!is_empty())
    {
        top--;
        count--;
        return true;
    }
    return false;
}

/**
#FUNCTION# =========================================================================
; Name...........: bool push(T item)
; Description....: Function that will add a variable to the stack.
; Syntax.........: object_name.push(item)
; Parameters.....: A) item        - represents data to be added to the stack.
; =================================================================================*/
template <class T>
bool Stack<T>::push(T item)
{
    if(!is_full())
    {
        list[++top] = item;
        count++;
        return true;
    }
    return false;
}

/**
#FUNCTION# =========================================================================
; Name...........: int get_size()
; Description....: Function that will return the size of the stack.
; Syntax.........: object_name.get_size()
; Parameters.....: NONE
; =================================================================================*/
template <class T>
int Stack<T>::get_size()
{
    return count;
}

/**
#FUNCTION# =========================================================================
; Name...........: T get_top()
; Description....: Function that will return the top most data variable from
;                  the stack.
; Syntax.........: object_name.get_top()
; Parameters.....: NONE
; =================================================================================*/
template <class T>
T Stack<T>::get_top()
{
    return list[top];
}

/**
#FUNCTION# =========================================================================
; Name...........: bool is_full()
; Description....: Function that will test if the stack is full.
; Syntax.........: object_name.is_full()
; Parameters.....: NONE
; =================================================================================*/
template <class T>
bool Stack<T>::is_full()
{
    return count == 10;
}

/**
#FUNCTION# =========================================================================
; Name...........: bool is_empty()
; Description....: Function that will test if the stack is empty.
; Syntax.........: object_name.is_empty()
; Parameters.....: NONE
; =================================================================================*/
template <class T>
bool Stack<T>::is_empty()
{
    return count == 0;
}
