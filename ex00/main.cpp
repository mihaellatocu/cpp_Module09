#include <iostream>
#include "BitcoinExchange.hpp"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Error, could not open file.\n";
        return (1);
    }
    BitcoinExchange btc("data.csv");
    btc.processInput(argv[1]); // input.txt
    return (0);
}