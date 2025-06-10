#pragma once
#include <iostream>
#include <fstream> // for ifstream - deschide fisier
#include <sstream> // for istringstream // separa linia
#include <map>
#include <cstdlib> // for std::atof
#include <iomanip> // for setprecision
#include <string>


class BitcoinExchange
{
private:
    std::map<std::string, float> _database; // data and price

    void loadDatabase(const std::string& filename); // adding data.csv in map
    bool isValidValue(const std::string& valueStr, float& value) const; // check if value is between 0 and 1000
    bool isValidDate(const std::string& date_) const; // check valid date

public:
    BitcoinExchange(const std::string& databaseFile);
    void processInput(const std::string& inputFile); // read input.txt and process data
    ~BitcoinExchange();
};


