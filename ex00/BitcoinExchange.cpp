/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   BitcoinExchange.cpp                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/25 13:51:30 by ageels        #+#    #+#                 */
/*   Updated: 2023/09/25 17:53:56 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

void	BitcoinExchange::message(const std::string str){
	std::cout << "\x1B[35m BitcoinExchange - " << str << "\x1B[0m" << std::endl;	
};

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

std::ostream 	&operator<<(std::ostream &o, BitcoinExchange &src) {
	o << "hey";
	(void)src;
	return (o);
}