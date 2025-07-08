#include <iostream>
#include <string.h>
#include <map>
#include <fstream>
#include <sstream>
#include <cstdlib> // for std::atof
#include <iomanip>

class BTC
{
private:
    std::map<std::string, float> _database;
    std::string _data;
    int value;
    void loadDatabase(std::string filename);
    bool checkValidData(std::string data);
    bool checkValue(float value);

public:
    BTC(std::string databaseFile);
    void run(const std::string &inputfile);
    ~BTC();
};

BTC::BTC(std::string databaseFile)
{
    loadDatabase(databaseFile);
}

BTC::~BTC(){}

void BTC::loadDatabase(std::string filename)
{
    std::ifstream file(filename.c_str());
    std::string line;
    if (!file.is_open())
    {
        std::cerr << "File cannot be opened.\n" << std::endl;
        return ;
    }
    std::getline(file, line); //skip first line
    //std::cout <<  line << std::endl;
   
    while (getline(file, line))
    {
        std::string data;
        std::string valueStr;
        std::istringstream iss(line);
        if (!getline(iss, data,',') || !getline(iss, valueStr))
            continue;
        float price = std::atof(valueStr.c_str());
        _database[data] = price;
    }

}

bool BTC::checkValidData(std::string data)
{
    if (data.length() != 10 || data[4] != '-' || data[7] != '-')
        return false;
    int year, month, day;
    
    year = atoi((data.substr(0, 4).c_str()));
    month = atoi((data.substr(5,2).c_str()));
    day = atoi((data.substr(8, 2)).c_str());

    if (month < 1 || month > 12)
        return false;
    static const int daysInMonth[] = { 31, 28, 31, 30, 31, 30,
                                    31, 31, 30, 31, 30, 31};
    int maxDay = daysInMonth[month - 1];
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) ||  year % 400 == 0))
        maxDay = 29;

    if (day < 1 || day > maxDay)
        return false;
    return true;
}

bool BTC::checkValue(float value)
{
    if (value < 0)
    {
        std::cerr << "Error: not a positive nr.\n";
        return false;
    }
    else if (value > 1000)
    {
        std::cerr << "Error: too large a number.\n";
        return false;
    }
    return true;
}

void BTC::run(const std::string& inputfile)
{
    std::ifstream file(inputfile.c_str());
    std::string line;
    std::getline(file, line); //skip title

    while (std::getline(file, line))
    {
        std::string data;
        std::string valueStr;
        char separator;
        std::istringstream iss(line);
        iss >> data >> separator >> valueStr;
        //std::cout << data << " -- " << separator << " -- " << valueStr << std::endl; 
        if (data.empty() || valueStr.empty())
        {
            std::cerr << " The data or value are missing.\n";
            continue;
        }
        if (!checkValidData(data))
        {
            std::cerr << "Bad input =>> " << data << std::endl;
            continue;
        }
        float value = atof(valueStr.c_str());
       
       if (!checkValue(value))
        {
            //std::cerr << "Values is incorrect =>> " << value << std::endl;
            continue;
        }
        std::map<std::string, float>::iterator it;
        it = _database.lower_bound(data);
        
        if (it->first != data || it == _database.end())
        {
            if (it == _database.begin())
            {
                std::cerr << "Error: no earlier date available in database." << std::endl;
				continue;
            }
            --it;
        }
        std::cout << it->first << " Pretul =>> " << std::fixed << std::setprecision(2) << it->second * value << std::endl;
    }


}

/*

"client %d : left"
char* = client ;
char* =  : left:
str = itoa(5)
sprintf(str*, "client %d : left", 5)
*/