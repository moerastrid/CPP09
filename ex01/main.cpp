/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/03 13:06:54 by ageels        #+#    #+#                 */
/*   Updated: 2024/01/03 14:12:07 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>
	using std::cout;
#include <string>
	using std::string;

enum expression {
	ERROR,
	WHITESPACE,
	NUMBER,
	OPERATION
};

static expression	parse(string arg) {
	cout << "parsing ..." << arg << "...\n";
	if (arg.empty())
		return (WHITESPACE);
	if (arg.length() != 1)
		return (ERROR);
	char ch = arg[0];
	if (isspace(ch) == true)
		return (WHITESPACE);
	if (isdigit(ch) == true)
		return (NUMBER);
	if (arg.find_first_of("+-/*") != std::string::npos)
		return(OPERATION);
	return (ERROR);
}

int main(int argc, char **argv) {
	RPN	rpn;
	(void)argv;

	if (argc == 1) {
		cout << "error : please enter calculation";
	}

	for(auto i = 1; i < argc; i++) {
		if (argv[i])
			switch (parse(argv[i])) {
				case (WHITESPACE) :
					break;
				case (ERROR) :
					cout << "parse error\n";
					return(-1);
				case (NUMBER) :
					cout << "number!\n";
					continue;
				case (OPERATION) :
					cout << "operation!\n";
					continue;
			}
	}
	cout << "This is RPN: " << rpn << "\n";
	return (1);
}