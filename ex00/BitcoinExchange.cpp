/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   BitcoinExchange.cpp                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/25 13:51:30 by ageels        #+#    #+#                 */
/*   Updated: 2024/01/02 14:41:44 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

// PRIVATE 

void	BitcoinExchange::message(const std::string str) {
	std::cout << "\x1B[34mBitcoinExchange - " << str << "\x1B[0m" << std::endl;	
}

// PUBLIC (OC FORM)

BitcoinExchange::BitcoinExchange() {
	message("default constructor");
}

BitcoinExchange::~BitcoinExchange() {
	message("default destructor");
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src) {
	message("copy constructor");
	*this = src;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &src) {
	message("assignment operator");
	this->dataMap = src.dataMap;
	return(*this);
}


// CUSTOM PUBLIC 

bool	BitcoinExchange::setDB() {
	std::map<std::string, int>	newMap;

	std::fstream	csvFile;
	csvFile.open("data.csv", std::fstream::in);
	if (!csvFile.is_open()) {
		message("Error: could not open .csv file");
		return (false);
	}

	csvFile.close();
	return (true);
}

void	BitcoinExchange::verifyInput(std::string input) {
	// std::string	date;
	// int			value;

	if (input.find('|') == std::string::npos)
		throw (BitcoinExchangeException("Error: bad input => " + input));
	
	// verify input
}

std::string	BitcoinExchange::exchange(std::string input) {
	verifyInput(input);
	// find matching value in csv file & return it
	return ("1");
}

std::ostream 	&operator<<(std::ostream &o, BitcoinExchange &src) {
	o << "hey";
	(void)src;
	return (o);
}