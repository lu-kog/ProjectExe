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

    return currentOperator->data.value;
}

void test_cases()
{

    std::string expressions[] = {
        "((5+3)*(2+(8/4))-(6/3))",
        "(2*(3+(4*(5-1))))",
        "((8+(6/3))*2)-(7-1)",
        "((3+2)*(5-(4/2)))/3",
        "((10-(5*2))+(8/2))/2",
        "((7+(8*2))/(3-(1*1)))",
        "(9*(2+(4/2))-(6/3))",
        "((5+(2*(3-1)))/(4-2))+6",
        "((4+(3*5))-(6/2))*(2+1)",
        "(8*((2+(3*2))-1)/(4-1))",
        "((3+(4*2))-(7/1))*((6/2)+1)",
        "(10+((8-6)*(5+1)))/2",
        "((2+3)*(4-(5/2)))/(1+2)",
        "((5*(4+(3*2)))-6)/(3-1)",
        "((9-((6/3)*2))+7)/(2+1)",
        "((8+(9-(5*2)))*3)/(4-1)",
        "(2+(3*(5-(7/2))))-4",
        "((10+(8-(2*3)))/2)+(4*2)",
        "(6+(7*(8-5)))/(4-2)",
        "((3*(4+(2/2)))-6)/(5-3)",
        "((7*(8-(2*4)))-1)+(9/3)",
        "(5+((3*2)+(6/2)))-4",
        "((9-((7/1)*2))+8)/3",
        "((8+(6*2))-((4/2)+1))",
        "(10/((3+(2*4))-5))+6",
        "((7*3)-(2+(4/2)))/(5-3)",
        "((4+(2*5))-(8/4))*((6-2)+1)",
        "((3*(4+(8/2)))-7)/((2+1)*2)",
        "((9-((6/3)*2))+5)*(4/2)",
        "((8+(7*3))-((2*5)/2))",
        "(5+((3*(4-(6/2)))-1))/2",
        "((7+(8*(9-5)))-(6/2))",
        "((2*(3+(5/2)))-4)/(6-3)",
        "((10-(4*2))+(8/2))*3",
        "((6/(2+1))*(5+(8-4)))",
        "((9+((7-2)*3))/2)+(4-1)",
        "((5+(3*(6-(4/2))))/2)-1",
        "((8-(3*2))+(5*2))/(4-1)",
        "(7*((4+(5/2))-(3/1)))-6",
        "((10/((2*3)-1))+(5-3))*2",
        "((8+(9-5))*2)/(4+1)",
        "((3+(4*2))-(7/(2+1)))*2",
        "(6+((7*(8-(3/1)))-4))/2",
        "((9+(3*(2-(6/3))))/3)-1",
        "((5*(6-4))+(8/2))/((3+1)-2)",
        "((7+(8*2))/(4-1))+(5-3)",
        "((10-(3+(2*2)))*2)/((4/2)+1)",
        "((8+(9-(5*2)))*(3/1))/2/3+2/2+24424+54*(3782+(76+(178*09-9*(865+865 /(65+90*(5789+34567))))))",
        "((4+(5*(2-(3/1))))/2)-1"};

    double expectedResults[] = {
        30.0,                // ((5+3)*(2+(8/4))-(6/3))
        38.0,                // (2*(3+(4*(5-1))))
        14.0,                // ((8+(6/3))*2)-(7-1)
        5.0,                 // ((3+2)*(5-(4/2)))/3
        2.0,                 // ((10-(5*2))+(8/2))/2
        11.5,                // ((7+(8*2))/(3-(1*1)))
        34.0,                // (9*(2+(4/2))-(6/3))
        10.5,                // ((5+(2*(3-1)))/(4-2))+6
        48.0,                // ((4+(3*5))-(6/2))*(2+1)
        18.67,               // (8*((2+(3*2))-1)/(4-1))
        16.0,                // ((3+(4*2))-(7/1))*((6/2)+1)
        11.0,                // (10+((8-6)*(5+1)))/2
        2.5,                 // ((2+3)*(4-(5/2)))/(1+2)
        22.0,                // ((5*(4+(3*2)))-6)/(3-1)
        4.0,                 // ((9-((6/3)*2))+7)/(2+1)
        7.0,                 // ((8+(9-(5*2)))*3)/(4-1)
        2.5,                 // (2+(3*(5-(7/2))))-4
        14.0,                // ((10+(8-(2*3)))/2)+(4*2)
        13.5,                // (6+(7*(8-5)))/(4-2)
        4.5,                 // ((3*(4+(2/2)))-6)/(5-3)
        18.5,                // ((7*(8-(2*4)))-1)+(9/3)
        10.0,                // (5+((3*2)+(6/2)))-4
        1.0,                 // ((9-((7/1)*2))+8)/3
        17.0,                // ((8+(6*2))-((4/2)+1))
        7.67,                // (10/((3+(2*4))-5))+6
        8.5,                 // ((7*3)-(2+(4/2)))/(5-3)
        60.0,                // ((4+(2*5))-(8/4))*((6-2)+1)
        2.83,                // ((3*(4+(8/2)))-7)/((2+1)*2)
        20.0,                // ((9-((6/3)*2))+5)*(4/2)
        24.0,                // ((8+(7*3))-((2*5)/2))
        3.5,                 // (5+((3*(4-(6/2)))-1))/2
        36.0,                // ((7+(8*(9-5)))-(6/2))
        2.33,                // ((2*(3+(5/2)))-4)/(6-3)
        18.0,                // ((10-(4*2))+(8/2))*3
        18.0,                // ((6/(2+1))*(5+(8-4)))
        15.0,                // ((9+((7-2)*3))/2)+(4-1)
        7.5,                 // ((5+(3*(6-(4/2))))/2)-1
        4.0,                 // ((8-(3*2))+(5*2))/(4-1)
        18.5,                // (7*((4+(5/2))-(3/1)))-6
        8.0,                 // ((10/((2*3)-1))+(5-3))*2
        4.8,                 // ((8+(9-5))*2)/(4+1)
        17.33,               // ((3+(4*2))-(7/(2+1)))*2
        18.5,                // (6+((7*(8-(3/1)))-4))/2
        2.0,                 // ((9+(3*(2-(6/3))))/3)-1
        7.0,                 // ((5*(6-4))+(8/2))/((3+1)-2)
        9.67,                // ((7+(8*2))/(4-1))+(5-3)
        2.0,                 // ((10-(3+(2*2)))*2)/((4/2)+1)
        -101121.61574279927, // ((8+(9-(5*2)))*(3/1))/2
        -1.5                 // ((4+(5*(2-(3/1))))/2)-1
    };

    // Print table header
    std::cout << std::setw(8) << "Test"
              << std::setw(45) << "Expression"
              << std::setw(30) << "Expected Result"
              << std::setw(15) << "Result"
              << std::endl;

    std::cout << std::setw(8) << "----"
              << std::setw(45) << "------------------------"
              << std::setw(30) << "------------------"
              << std::setw(15) << "------"
              << std::endl;

    for (int i = 0; i < sizeof(expressions) / sizeof(expressions[0]); ++i)
    {
        double result = evaluate(expressions[i]);
        std::cout << std::setw(8) << (result == expectedResults[i] ? "Pass" : "Fail")
                  << std::setw(45) << expressions[i]
                  << std::setw(30) << (expectedResults[i])
                  << std::setw(15) << (result)
                  << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    std::string invalidExpressions[] = {
        "(5+3)*",           // Missing closing parenthesis.
        "5+3)*2",           // Unbalanced parentheses.
        "((5+3)*2",         // Missing closing parenthesis.
        "5+(3*2",           // Missing closing parenthesis.
        "((5+3)*2/",        // Missing closing parenthesis.
        "5+3/0",            // Division by zero.
        "5/0+3",            // Division by zero.
        "((5+3)*2-(1+2",    // Missing closing parenthesis.
        "5++3",             // Double operator (incorrect syntax).
        "5+3*",             // Missing operand after operator.
        "((5+3)*2-(1+2))+", // Trailing operator without operand.
        "5+(3*2))",         // Unbalanced parentheses.
        "((5+3)*2",         // Missing closing parenthesis.
        "5+3*(2/",          // Missing closing parenthesis.
        "5*",               // Missing operand.
        "*5+3",             // Leading operator without operand.
        "5/(2+3))",         // Unbalanced parentheses.
        "((5+3)*(2/1))+",   // Trailing operator without operand.
        "5+*3",             // Misplaced operator.
        "5+(3*2",           // Missing closing parenthesis.
        "((5+3)*2/2",       // Missing closing parenthesis.
        "((5+3)*2)-",       // Trailing operator without operand.
        "5/(2+3/",          // Missing closing parenthesis.
        "5/((2+3",          // Missing closing parenthesis.
        "((5+3)*2/(1+))",   // Unbalanced parentheses.
        "5+(3*2-",          // Missing closing parenthesis.
        "((5+3)*(2-(1+2))", // Missing closing parenthesis.
        "5*(3+(2+))",       // Unbalanced parentheses.
        "((5+3)*(2/",       // Missing closing parenthesis.
        "5+(3*2))",         // Unbalanced parentheses.
        "((5+3)*(2+4",      // Missing closing parenthesis.
        "5/2+(3*2",         // Missing closing parenthesis.
        
    };

    for (auto &&st : invalidExpressions)
    {
        try
        {

            std::cout << evaluate(st) << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cout << e.what() << '\n';
        }
    }

    return 0;
}

#endif