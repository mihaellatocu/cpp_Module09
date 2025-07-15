#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>

class RPN
{
private:
    std::stack<int> s;
    int total;

    long long doMath(int a, int b, char op);
    
public:
    RPN(const std::string& ag); // it needs to be const?
    RPN(const RPN& other);
    RPN& operator=(const RPN& other);
    ~RPN();

   // void run(const std::string& ag);
};


