#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <iostream>
#include <cctype>
#include <string.h>
#include <stdio.h>
using namespace std;

class Calculator
{
    public:
        void Simulation();
        string convert_infix_to_postfix(string);
        int evaluate_postfix(string);
        bool checkString(string);

};

#endif // CALCULATOR_H
