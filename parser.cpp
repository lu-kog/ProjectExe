#ifndef parser

#define parser

#include <iostream>
#include <stack>
#include <cctype>
#include <string>
#include <map>
#include "myNode.h"

extern bool validateExp(std::string expr);
extern std::string removeSpaces(const std::string &expr);


double add(double &a, double &b)
{
    return a + b;
}

double subtract(double &a, double &b)
{
    return a - b;
}

double multiply(double &a, double &b)
{
    return a * b;
}

double divide(double &a, double &b)
{
    if (b == 0)
    {
        throw std::invalid_argument("Division by zero");
    }
    return a / b;
}



// operator precedence
std::map<char, int> precedence = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}};

std::string infixToPostfix(const std::string &infix)
{
    
    std::stack<char> operators;
    std::string postfix;

    for (int i = 0; i < infix.length(); i++)
    {

        if (std::isdigit(infix.at(i)))
        {
            // tokenize with seperator ~
            while (i < infix.length() && std::isdigit(infix.at(i)))
            {
                postfix += infix.at(i);
                i++;
            }
            i--;            // for move cursor at current non numuric char.
            postfix += '~'; // add seperator
        }
        else if (infix.at(i) == '(')
        {
            operators.push(infix.at(i));
        }
        else if (infix.at(i) == ')')
        {
            // append operators withing a scope ()
            while (!operators.empty() && operators.top() != '(')
            {
                postfix += operators.top();
                operators.pop();
            }
            operators.pop(); // Remove the '('
        }
        else if (precedence.find(infix.at(i)) != precedence.end())
        {
            // if operator
            while (!operators.empty() && precedence[operators.top()] >= precedence[infix.at(i)])
            {
                postfix += operators.top();
                operators.pop();
            }
            operators.push(infix.at(i));
        }
    }

    // append balance operators from stack
    while (!operators.empty())
    {
        postfix += operators.top();
        operators.pop();
    }

    return postfix;
}

myNode *postfixToLinkedList(std::string postfix)
{

    myNode *linkedNode=nullptr;
    myNode *lastNode=nullptr;

    for (int i = 0; i < postfix.length(); i++)
    {
        if (std::isdigit(postfix.at(i)))
        {
            std::string num;
            while (i < postfix.length() && postfix.at(i) != '~')
            {
                num += postfix.at(i);
                i++;
            }
            double fetchedNumber = std::stod(num); // parse string to number



            // create new node after current, and update the current node
            if (linkedNode)
            {
                lastNode->next = new myNode(fetchedNumber);
                lastNode->next->prev = lastNode;
                lastNode = lastNode->next;
            }
            else
            {
                linkedNode = new myNode(fetchedNumber);
                lastNode = linkedNode;
            }
        }
        else
        {
            switch (postfix.at(i))
            {
            case '+':
                lastNode->next = new myNode(add);
                break;
            case '-':
                lastNode->next = new myNode(subtract);
                break;
            case '*':
                lastNode->next = new myNode(multiply);
                break;
            case '/':
                lastNode->next = new myNode(divide);
                break;

            default:
                break;
            }

            lastNode->next->prev = lastNode;
            lastNode = lastNode->next;
        }
    }
    
    

    return linkedNode;
}




myNode* parse(std::string expr){
    std::string mod_expr = removeSpaces(expr);
    bool isValidExpr = validateExp(mod_expr);

    if (isValidExpr)
    {
        std::string postfix = infixToPostfix(mod_expr);
        return postfixToLinkedList(postfix);
    }else{
        throw std::invalid_argument("Invalid Expression! - " + expr);
    }
    
}


#endif
