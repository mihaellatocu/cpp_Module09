#include "PmergeMe.hpp"


int main(int ac, char* argv[])
{
    (void)argv;
    if (ac < 2)
    {
        std::cerr << "Please add values.\n";
        return 1;
    }
    std::cout << "test from main\n";
    return (0);
}