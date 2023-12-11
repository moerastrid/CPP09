/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   BitcoinExchange.cpp                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/25 13:51:30 by ageels        #+#    #+#                 */
/*   Updated: 2023/12/11 18:35:00 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

void	BitcoinExchange::message(const std::string str) {
	std::cout << "\x1B[34mBitcoinExchange - " << str << "\x1B[0m" << std::endl;	
}

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
	(void)src;
	return (*this);
}

std::string	BitcoinExchange::exchange(std::string input) {
	if (input.find('|') == std::string::npos)
		throw (BitcoinExchangeException("Error: bad input => " + input));
	// verify input
	// find matching value in csv file & return it
	return ("1");
}

std::ostream 	&operator<<(std::ostream &o, BitcoinExchange &src) {
	o << "hey";
	(void)src;
	return (o);
}