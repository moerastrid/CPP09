/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   BitcoinExchange.cpp                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/25 13:51:30 by ageels        #+#    #+#                 */
/*   Updated: 2024/01/03 13:33:50 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

// PRIVATE 

void	BitcoinExchange::message(const std::string str) {
	std::cout << "\x1B[34mBitcoinExchange - " << str << "\x1B[0m" << std::endl;	
}

// PUBLIC (OC FORM)

BitcoinExchange::BitcoinExchange() {
	//message("default constructor");
}

BitcoinExchange::~BitcoinExchange() {
	//message("default destructor");
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src) {
	//message("copy constructor");
	*this = src;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &src) {
	//message("assignment operator");
	this->dataMap = src.dataMap;
	return(*this);
}


// CUSTOM PUBLIC 
	
	
		// float	exchange_rate = std::stof(line.substr(line.find_first_of(',') +1));
		// number always starts at pos 11 (yyyy-mm-dd,N)
bool	BitcoinExchange::setDB() {
	std::map<std::string, int>	newMap;

	std::fstream	csvFile;
	csvFile.open("data.csv", std::fstream::in);
	if (!csvFile.is_open()) {
		message("Error: could not open .csv file");
		return (false);
	}
	
	std::cout << "\n START CSV DATA " << std::endl;
	for(std::string line; std::getline(csvFile, line);) {
		if (line == "date,exchange_rate")
			continue ;
		std::string	date = line.substr(0, 10);
		float		exchange_rate = std::stof(&line[11]);

		//std::cout << "Date: " << date << "\texchange_rate: " << exchange_rate << '\n';
		this->dataMap.insert(std::pair<std::string, float>(date, exchange_rate));
	}
	std::cout << " END CSV DATA \n" << std::endl;
	csvFile.close();
	return (true);
}

void	BitcoinExchange::verifyInput(std::string input) {
	if (input.find_first_of('|') != 11)
		throw (BitcoinExchangeException("Error: bad input => " + input));
}

std::string	BitcoinExchange::verifyDate(std::string date) {
	if (date.find_first_of('-') != 4 || date.find_last_of('-') != 7)
		throw (BitcoinExchangeException("Error: invalid date format, please use yyyy-mm-dd"));
	int year = stoi(date.substr(0,4));
	int month = stoi(date.substr(5, 2));
	int day = stoi(date.substr(8, 2));

	if ((year < 2009 || year > 2024) || (month < 0 || month > 12) || (day < 0 || day > 31))
		throw (BitcoinExchangeException("Error: invalid date"));
	return(date);
}

float	BitcoinExchange::verifyValue(std::string input) {
	float value = std::stof(&input[13]);

	if (value < 0)
		throw (BitcoinExchangeException("Error: not a positive number."));
	else if (value > 1000)
		throw (BitcoinExchangeException("Error: too large a number."));
	return(value);
}

std::string	BitcoinExchange::exchange(std::string input) {
	verifyInput(input);
	std::string date = verifyDate(input.substr(0, 10));
	float value = verifyValue(input);
	
	std::map<std::string, float>::iterator itd;
	itd = dataMap.lower_bound(date);
	if (itd->first != date) {
		itd--;
	}
	
	float result = value * itd->second;
	
	std::cout << "\x1B[36m" << date << " => " << value << " = " << std::setprecision(4) << result << "\x1B[0m" << "\n";
	// find matching value in csv file & return it
	return ("1");
}
