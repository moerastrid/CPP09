/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/25 13:51:38 by ageels        #+#    #+#                 */
/*   Updated: 2024/01/02 13:35:17 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include "BitcoinExchange.hpp"

void	errormessage(std::string str) {
	std::cout << "\x1B[31m" << str << "\x1B[0m" << std::endl;	
};

int main(int argc, char **argv) {
	if (argc != 2) {
		errormessage("USAGE: ./btc [inputfile]");
		return (-1);
	}
	
	BitcoinExchange btc;
	std::fstream	inFile;

	inFile.open(argv[1], std::fstream::in);
	if (!inFile.is_open())
		errormessage("Error: could not open input file");
	//std::cout << inFile.rdbuf() << std::endl;
	for (std::string line; std::getline(inFile, line);) {
		if (line == "date | value")
			continue ;
		std::cout << " | " << line << " | " << std::endl;
		try {
			btc.exchange(line);
		} catch (const BitcoinExchange::BitcoinExchangeException &ex) {
			std::cerr << "\x1B[31m" << ex.what() << "\x1B[0m" << std::endl;
		}
	}
	
	inFile.close();
	
	
}
