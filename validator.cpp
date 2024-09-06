#ifndef validator

#define validator

#include <iostream>
#include <stack>
#include <cctype> // for isdigit and isalpha
#include <string>

#define isOperator(ch) ((ch) == '+' || (ch) == '-' || (ch) == '*' || (ch) == '/')



std::string removeSpaces(const std::string &expr)
{
    std::string result;
    result.reserve(expr.size()); // Reserve space to avoid multiple allocations

    for (char ch : expr)
    {
        if (ch != ' ')
        {
            result += ch;
        }
    }

    return result;
}

bool hasValidCharacters(const std::string &expr)
{
    for (char ch : expr)
    {
        if (!isdigit(ch) && !(isOperator(ch)) && ch != '(' && ch != ')')
        {
            std::cout << "Invalid character: " << ch << std::endl;
            return false;
        }
    }
    return true;
}

bool hasBalancedParanthesis(const std::string &expr)
{

    std::stack<char> s;
    for (char ch : expr)
    {
        if (ch == '(')
        {
            s.push(ch);
        }
        else if (ch == ')')
        {
            if (s.empty() || s.top() != '(')
            {
                std::cout << "Unmatched paranthesis" << std::endl;
                return false;
            }
            s.pop();
        }
    }
    if (s.empty())
    {
        return true;
    }
    else
    {
        std::cout << "Unmatched paranthesis" << std::endl;
        return false;
    }
}

bool hasValidOperatorUsage(const std::string &expr)
{
    
    if (isOperator(expr.at(0)))
    {
        // start with operator, other than negative number
        if (expr.at(0) != '-')
        {
            std::cout << "Invalid operator usage: " << 0 << std::endl;
            return false;
        }
    }

    if (isOperator(expr.at(expr.size() - 1)))
    {
        std::cout << "Invalid operator usage: " <<expr.size()-1<< std::endl;
        return false;
    }

    int i = 0;
    for (char ch : expr)
    {
        if (isOperator(ch))
        {
            /*
                if(operator)
                  - before: ')' or n
                  - after: '(' or n or -
                  if(-) it must be a negative number.
            */

            bool beforeCondition = (expr[i - 1] == ')') || (isdigit(expr[i - 1]));
            bool afterCondition = (expr[i + 1] == '(') || (isdigit(expr[i + 1])) || (expr[i + 1] == '-');

            if (!(beforeCondition && afterCondition)){
                return false;
            }
            else if ((expr[i + 1] == '-') && !isdigit(expr[i + 2]))
            {
                return false;
            }
            
        }
        i++;
    }
    return true;
}

bool validateExp(std::string expr)
{
    return hasValidCharacters(expr) && hasBalancedParanthesis(expr) && hasValidOperatorUsage(expr);
}



#endif