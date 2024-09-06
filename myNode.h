#ifndef Noder
#define Noder

#include <iostream>
typedef double (*operatorPT)(double &a, double &b);

class myNode
{

public:
    union dt // It can be a number or a operator function
    {
        double value;
        operatorPT op;
    } data;
    bool is_operator;
    myNode *next;
    myNode *prev;

    myNode(double num)
    {
        data.value = num;
        is_operator = false;
        next = nullptr; prev = nullptr;
    }

    myNode(operatorPT func)
    {
        data.op = func;
        is_operator = true;
        next = nullptr; prev = nullptr;

    }
};

#endif
