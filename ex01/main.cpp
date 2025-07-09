#include "RPN.hpp"


int main(int ac, char* argv[])
{
    if (ac != 2 || !argv[1] || argv[1][0] == '\n')
    {
        std::cerr << "Error: please add correctly the argument format.\n";
        return 1; 
    }

    RPN(std::string(argv[1]));
    return (0);
}