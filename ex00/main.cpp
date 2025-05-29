#include <iostream>
#include "BitcoinExchange.hpp"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Error, the file is missing or couldn't be opened.\n";
        return (1);

    }
    BitcoinExchange btc("data.csv");
    // btc.processing(argv[1]);
    return (0);
}