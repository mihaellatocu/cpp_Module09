#include "RPN.hpp"

RPN::RPN(const RPN& other)
{
    total = other.total;
    s = other.s;
}
RPN& RPN::operator=(const RPN& other)
{
    if ( this != &other)
    {
        total = other.total;
        s = other.s;
    }
    return *this;
}


bool issign(char sign)
{
    if (sign == '+' || sign == '-' || sign == '*' || sign == '/' )
        return true; 
    return false;
}

long long RPN::doMath(int a, int b, char op)
{
    if (op == '-')
        return (static_cast<long long>(a) - b);
    else if (op == '*')
        return (static_cast<long long>(a) * b);
    else if (op == '/')
        return (static_cast<long long>(a) / b);
    else
        return (static_cast<long long>(a) + b);
}

RPN::RPN(const std::string& ag)
{
    if (ag.empty())
    {
        (std::cerr << "The ag is empty.\n");
        return ;
    }
    int i = 0;
    while (ag[i])
    {
        if (isdigit(ag[i]))
        {
            s.push(ag[i] - '0');
            std::cout << ag[i] - '0' << " ";
        }
        else if (issign(ag[i]))
        {
            if (s.size() < 2)
            {
                std::cerr << "Error: One digit is missing.\n";
                return;
            }
            int a = s.top();
            std::cout << " a: " << a << " ";
            s.pop();
            int b = s.top();
            std::cout << " b: " << b << " ";
            s.pop();
            if (a == 0 && ag[i] == '/')
            {
                std::cerr << "Error: The divizion to 0 is not valid.\n";
                return ;
            }
            long long c = doMath(b, a, ag[i]);
            std::cout << " c is: " << c << std::endl;
            if (c > INT32_MAX || c < INT32_MIN)
            {
                std::cerr << "Error: overflow.\n";
                return ;
            }
            s.push(static_cast<int>(c));
        }
        else if (ag[i] != ' ' && ag[i] != '\t')
        {    
            std::cerr << "Error: the values are not valid.\n";
            return;
        }
        i++;
    }
    if(s.size() > 1)
    {
        std::cerr << "Error: the values are not valid.\n";
        return;
    }
    else if(s.size() == 1)
        total = s.top();
    else
        total = 0;
    std::cout << "total: " << total << std::endl;
}

RPN::~RPN(){}