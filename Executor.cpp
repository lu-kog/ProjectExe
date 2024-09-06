#ifndef Executor
#define Executor
#include "myNode.h"
#include <iostream>
#include <iomanip>
#include <string>

myNode *parse(std::string expr);

double evaluate(std::string expr)
{
    myNode *currentOperator = parse(expr); // get the linked listed nodes

    while (currentOperator)
    {
        /*
            if number, move cursor to the next node,
            if operator, evaluate and move cursor to evaluated value
            break at the end of node..
        */

        if (currentOperator->is_operator)
        {

            myNode *right = currentOperator->prev;
            myNode *left = right->prev;

            double value = currentOperator->data.op(left->data.value, right->data.value);
            left->data.value = value;

            left->next = currentOperator->next;

            if (currentOperator->next)
            {
                currentOperator->next->prev = left; // segfault in case: 1 1 +
            }

            delete right;
            delete currentOperator;

            currentOperator = left;
        }
        else
        {
            if (currentOperator->next)
            {
                currentOperator = currentOperator->next;
            }
            else
            {
                break;
            }
        }
    }

    double result = currentOperator->data.value;
    delete currentOperator;

    return result;
}


extern void valid_test_cases();
extern void invalid_test_cases()

int main(int argc, char const *argv[])
{   
    std::cout << evaluate("1+1") << std::endl;
    return 0;
}

#endif