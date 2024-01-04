/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/03 13:06:54 by ageels        #+#    #+#                 */
/*   Updated: 2024/01/04 16:30:49 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>
	using std::cout;
	using std::cerr;
#include <string>
	using std::string;



int main(int argc, char **argv) {
	RPN	rpn;
	(void)argv;

	if (argc == 1) {
		cout << "error : please enter calculation";
	}

	for (int i = 1; argv[i]; i++) {
		try {
			rpn.calculate(argv[i]);
			cout << rpn << "\n";
		} catch (const RPN::RPNException &ex) {
			cerr << "\x1B[31m" << ex.what() << "\x1B[0m" << std::endl;		
		}
		rpn.reset();
	}
	return (1);
}
