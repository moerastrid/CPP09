/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/25 13:51:38 by ageels        #+#    #+#                 */
/*   Updated: 2023/09/25 17:56:30 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <string>

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
		errormessage("Error: could not open file");
	std::cout << inFile.rdbuf() << std::endl;
	inFile.close();
}
