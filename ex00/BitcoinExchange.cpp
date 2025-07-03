#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(const std::string& databaseFile)
{
	loadDatabase(databaseFile);
}

BitcoinExchange::~BitcoinExchange()
{
}

void BitcoinExchange::loadDatabase(const std::string& filename)
{
	std::map<std::string, float>::iterator it;
	std::ifstream file(filename.c_str());
	std::string line;

	if (!file.is_open())
	{
		std::cerr << "Error: could not open database file.\n";
		return ;
	}
	std::getline(file, line); // skip first line 
	// while(std::getline(file, line))
	// {
	// 	++i;
	// 	std::cout << i << " - " <<  line << "\n";
	// }
	while(std::getline(file, line))
	{
		std::istringstream ss(line);
		std::string date, priceStr;

		//read up to , and save the info in date 
		//continue reading and save the rest of the line into priceStr
		//if any of them are missing ignore and skip the line
		if (!std::getline(ss, date, ',') || !std::getline(ss, priceStr))
			continue;
	
		float price = std::atof(priceStr.c_str());
		_database[date] = price;
	}
	// for (it = _database.begin(); it != _database.end(); it++)
	// 	std::cout << (*it).first << " - " << std::fixed << std::setprecision(2) << (*it).second << "\n";

}


bool BitcoinExchange::isValidDate(const std::string& date_) const
{
	if(date_.length() != 10 || date_[4] != '-' || date_[7] != '-')
		return false;
	int year, month, day;
	try {
		year = std::atoi(date_.substr(0, 4).c_str()); 
		month = std::atoi(date_.substr(5, 2).c_str());
		day = std::atoi(date_.substr(8, 2).c_str()); // sau std::istringstream(dateStr.substr(8, 2)) >> day;
	} catch(std::exception &e)
	{
		return false;
	}
	if (month < 1 || month > 12)
		return false;
	static const int daysInMonth[] = { 31, 28, 31, 30, 31, 30,
									31, 31, 30, 31, 30, 31};
	int maxDay = 	daysInMonth[month - 1];
	
	if (month == 2 &&
		((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
			maxDay = 29;

	if (day < 1 || day > maxDay)
		return false;
	return true;
}

bool BitcoinExchange::isValidValue(const std::string& valueStr, float& value) const
{
	std::istringstream ss(valueStr);
	ss >> value; // for int float etc
	
	if (ss.fail() || !ss.eof())
		return false;
		
	if (value < 0.0f || value > 1000.0f) 
		return false;
	
	return true;
}

void BitcoinExchange::processInput(const std::string& inputFile)
{
	std::ifstream file(inputFile.c_str());
	std::string line;

	if (!file)
	{
		std::cerr << "Error: could not open file.\n";
		return;
	}
	

	std::getline(file, line); // skip title

	while (std::getline(file, line))
	{
		std::string date_, valueStr;
		std::istringstream ss(line);
		
		size_t sep = line.find('|');
		if (sep == std::string::npos)
		{
			std::cerr << "Error bad input => " << line << std::endl;
			continue;
		}
		date_ = line.substr(0, sep);
		valueStr = line.substr(sep + 1);
		// Elimină spații la început și final
		date_.erase(0, date_.find_first_not_of(" \t"));
		date_.erase(date_.find_last_not_of(" \t") + 1);
		valueStr.erase(0, valueStr.find_first_not_of(" \t"));
		valueStr.erase(valueStr.find_last_not_of(" \t") + 1);

		
		if(!isValidDate(date_))
		{
			std::cerr << "Error: bad input => " << line << std::endl;
            continue;
		}
		// to remove spaces in lines
		float value;
		if (!isValidValue(valueStr, value))
		{
			if (value < 0)
				 std::cerr << "Error: not a positive number." << std::endl;
			else
				std::cerr << "Error: too large a number." << std::endl;
			continue;
		}
		// Caută cursul BTC pentru data respectivă sau cea mai apropiată anterioară
		std::map<std::string, float>::iterator it;
		it = _database.lower_bound(date_); // cauta data exacta sau urmatoarea mai mare
        
        if ((*it).first != date_ || it == _database.end())
        {
            if (it == _database.begin())
            {
                std::cerr << "Error: no earlier date available in database." << std::endl;
				continue;
            }
            --it;
        }
        //std::cout << "Data este:        " << (*it).first << std::endl;
	
		//Afisam res calculului
		std::cout << date_ << ": => " << value << " = "
			<< std::fixed << std::setprecision(2) << (value * it->second) << std::endl;
	}
}