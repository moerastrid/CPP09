/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/25 13:51:38 by ageels        #+#    #+#                 */
/*   Updated: 2023/10/04 15:06:11 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <string>
#include "BitcoinExchange.hpp"

void	errormessage(std::string str) {
	std::cout << "\x1B[31m" << str << "\x1B[0m" << std::endl;	
};

int main(int argc, char **argv) {
	if (argc != 2) {
		errormessage("Error: argument count");
		return (-1);
	}

	std::fstream	inFile;

	inFile.open(argv[1], std::fstream::in);
	if (!inFile.is_open())
		errormessage("Error: could not open input file");
	std::cout << inFile.rdbuf() << std::endl;
	inFile.close();

	std::fstream	dataFile;
	dataFile.open("data.csv", std::fstream::in);
	if (!dataFile.is_open())
		errormessage("Error: could not open data.csv");
	dataFile.close();
	
	BitcoinExchange my_btc;
	return (0);
}
