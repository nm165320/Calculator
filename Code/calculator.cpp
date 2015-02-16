// Calculator.cpp Function Definitions
#include "Calculator.h"
#include "Stack.cpp"

/**
#FUNCTION# =========================================================================
; Name...........: void simulation()
;
; Description....: Function that will begin the process of accepting a string, in
;                  the form of an infix expression, and passing the string to other
;                  functions, in Calculator class, to convert the string into a
;                  postfix expression, and evaluating the postfix expression.
;
; Programmer.....: Nelson Matos
; Syntax.........: object_name.simulation();
; Parameters.....: A) NONE
; =================================================================================*/
void Calculator::Simulation()
{

    string infix, postfix;
    char ans;

    do
    {
        cout << "\nOne example of an infix expreesion is (7+3)/2."
             << "\nEnter an infix expression: ";
        getline(cin,infix);

        // Validating the string.

        while(!checkString(infix))
        {
                cout << "SYNTAX ERROR!\n"
                     << "\nOne example of an infix expreesion is (7+3)/2."
                     << "\nEnter an infix expression: ";
                getline(cin,infix);
        }

        // Converting the infix string and storing the result in postfix string.
        postfix = convert_infix_to_postfix(infix);

        // Statement to show infix conversion is converting correctly.
        //cout << "The postfix expression is " << postfix << "." << endl;

        // Displaying the answer.
        cout << "The answer is " << evaluate_postfix(postfix) << ".\n\n";

        // Allowing the user to enter another mathematical infix expression.
        cout << "Would you like to try again? (y or n)";
        cin >> ans;
        getchar();
    }
    while(toupper(ans) == 'Y');

}

/**
#FUNCTION# =========================================================================
; Name...........: string convert_infix_to_postfix(string infix)
;
; Description....: Function that will accept a string, representing an infix
;                  expression, and convert the string into a postfix expression.
;                  The function will complete this task by using the template
;                  Stack class.
;
; Programmer.....: Nelson Matos
; Syntax.........: object_name.convert_infix_to_postfix(infix);
; Parameters.....: A) infix   - represents a string needing to be converted into a
;                               a postfix expression.
; =================================================================================*/
string Calculator::convert_infix_to_postfix(string infix)
{
    string postfix;
    Stack<char> expression;

    for(int i = 0; i < infix.length();)
    {
        // Data variable to scan string left to rignt.
        char letter = infix[i];

        // First Case: Test if letter is a space.
        // If so, do nothing.
        if(letter == ' ')
        {
            ;
        }

        // Second case: Test if letter is a number.
        // Will also test if letter is following multiple digits.
        // If so, append letter to postfix string.
        else if(isdigit(letter))
        {
            postfix += letter;
            if(isdigit(infix[i+1]))
            {
                while(isdigit(infix[i+1]))
                {
                    postfix += infix[i+1];
                    i++;
                }
                postfix += ' ';
            }
            else
                postfix += ' ';
        }

        // Third Case: Test if letter is a group operator. IE: ( )
        else if(letter == '(')
            expression.push(letter);
        else if(letter == ')')
        {
            while(expression.get_top()!= '(')
            {
                postfix += expression.get_top();
                expression.pop();
            }
            expression.pop();
        }

        // Fourth case

        // Part A) Test if stack is empty and  if letter is an operator. If both conditions
        //         are met then letter is pushed into the stack.
        else if((expression.is_empty() || expression.get_top()=='(') && (letter=='+' || letter=='-' || letter=='*' || letter=='/'))
            expression.push(letter);

        // Part B) Test if stack is empty, test if letter is either * or / and has priority
        //         over the operators in the stack
        else if((!expression.is_empty()) && (letter=='*' || letter=='/') && (expression.get_top()=='+' || expression.get_top()=='-'))
            expression.push(letter);

        // Part C) Test if stack is empty, test if letter has <= priority over the operators in
        //         in the stack. If so append operators in postfix string.
        else if((!expression.is_empty()) && (letter=='+' || letter=='-') && (expression.get_top()=='+' || expression.get_top()=='-' || expression.get_top()=='*' || expression.get_top()=='/'))
        {
            while((!expression.is_empty()) && (letter=='+' || letter=='-') && (expression.get_top()=='+' || expression.get_top()=='-' || expression.get_top()=='*' || expression.get_top()=='/'))
            {
                postfix += expression.get_top();
                postfix += ' ';
                expression.pop();
            }
            expression.push(letter);
        }

        //Part D) Test if stack is empty, test if letter has equal priority over operators in the stack.
        //        If so, append operators to postfix string.
        else if((!expression.is_empty()) && (letter=='*' || letter=='/') && (expression.get_top()=='*' || expression.get_top()=='/'))
        {
            while((!expression.is_empty()) && (letter=='*' || letter=='/') && (expression.get_top()=='*' || expression.get_top()=='/'))
            {
                postfix += expression.get_top();
                postfix += ' ';
                expression.pop();
            }
            expression.push(letter);
        }
        i++;
    }

    // Loop to append any leftover operators, in the stack, to
    // postfix string.
    while(!expression.is_empty())
    {
        postfix += expression.get_top();
        postfix += ' ';
        expression.pop();
    }

    return postfix;
}

/**
#FUNCTION# =========================================================================
; Name...........: int evaluate_postfix(string post_exp)
;
; Description....: Function that will accept a string, representing a postfix
;                  expression, and evaluate the contents of the string. After
;                  evalution, the function will return the result as an int.
;                  The function will complete this task by using the template
;                  Stack class.
;
; Programmer.....: Kaothar Sowemimo
; Syntax.........: object_name.evaluate_postfix(post_exp);
; Parameters.....: A) post_exp  - represents a string in postfix form. The function
;                                 will use the string contents, for evaluation.
; =================================================================================*/
int Calculator::evaluate_postfix(string post_exp)
{

    Stack <int> operands;
    int op1, op2, temp;

    for (int i=0; i < post_exp.length();)
    {
        if ( post_exp[i] == ' ')
        {
            i++; //do nothing and go to next
        }

        else if ( isdigit (post_exp[i]))
        {
            temp = post_exp[i] - '0';
            while ( isdigit (post_exp[i+1])) //multiple digit number

            {
                temp = temp *10 + post_exp[i+1] - '0';
                i++; //go to next digit
            }
            operands.push (temp);
            i++; //skip a space
        }
        else
        {
            switch (post_exp[i])
            {
            case '+':
                op1 = operands.get_top();
                operands.pop();
                op2 = operands.get_top();
                operands.pop();
                operands.push(op1+op2);
                break;

            case '-':
                op1 = operands.get_top();
                operands.pop();
                op2 = operands.get_top();
                operands.pop();
                operands.push(op2-op1);
                break;

            case '*':
                op1 = operands.get_top();
                operands.pop();
                op2 = operands.get_top();
                operands.pop();
                operands.push(op1*op2);
                break;

            case '/':
                op1 = operands.get_top();
                operands.pop();
                op2 = operands.get_top();
                operands.pop();
                operands.push(op2/op1);
                break;
            default:
                cout<<"\nInvalid operator. \n";

            }
            i++;
        }
    }

    if (!operands.is_empty())
        return operands.get_top();

    else
    {
        cout << "ERROR" << endl;
        return 0;
    }

}

/**
#FUNCTION# =========================================================================
; Name...........: bool checkString(string str)
;
; Description....: Function that will accept a string, representing an user input.
;                  The string should contain a mathematical expression in infix form.
;                  This function will check the validity of the user input. If the
;                  string passes validation, then the program will proceed. If the
;                  string does not pass validation, then the program will display an
;                  an error and will also the user to enter another input.
;
; Programmer.....: Josh Meeks
; Syntax.........: object_name.checkString(str)
; Parameters.....: A) str     - represents an user input. The string should contain
;                               a mathematical expression in infix form.
; =================================================================================*/
bool Calculator::checkString(string str)
{

    int openPar = 0;
    int closePar = 0;
    int operand = 0;
    int operatorCNT = 0;

    for(int i = 0; i < str.length();)
    {
        char temp = str[i];

        if(isalpha(temp) || temp== '{' || temp == '}' || temp == '[' || temp == ']')
            return false;

        else if(temp == ' ')
                ;
        else if(isdigit(temp))
        {
            if(isdigit(str[i+1]))
            {
                while(!isdigit(str[i+1]))
                    i++;
            }
            else
                operand++;
        }

        else if(temp == '(')
            openPar++;

        else if(temp == ')')
            closePar++;

        else if(temp == '+' || temp == '-' || temp == '*' || temp == '/')
            operatorCNT++;

        i++;
    }

        if(openPar == closePar && operand == operatorCNT+1)
            return true;

        else
            return false;

}
