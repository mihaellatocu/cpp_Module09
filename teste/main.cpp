#include "BTC.hpp"

int main(int ac, char* av[])
{
    if (ac != 2)
    {
        std::cout << "file is missing.\n";
        return (1);
    }
    BTC btc("data.csv");
    btc.run(av[1]);
   
    return 0;
}