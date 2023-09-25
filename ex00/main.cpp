/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/25 13:51:38 by ageels        #+#    #+#                 */
/*   Updated: 2023/09/25 16:15:14 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

void	errormessage(std::string str) {
	std::cout << "\x1B[31m" << str << "\x1B[0m" << std::endl;	
};

int main(int argc, char **argv) {
	if (argc != 2)
		errormessage("incorrect input");
	else
		(void)argv;
}
