/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/04 18:02:34 by ageels        #+#    #+#                 */
/*   Updated: 2024/01/08 21:06:31 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
	using std::cout;
	using std::cerr;
#include <string>
	using std::string;

#include "PmergeMe.hpp"


int main(int argc, char **argv) {
	PmergeMe	PmergeSorter;

	try {
		PmergeSorter.run(argc, argv);
	} catch (const PmergeMe::PmergeMeException &ex) {
		cerr << "\x1B[31m" << ex.what() << "\x1B[0m" << std::endl;
		return(-1);
	}
	//cout << PmergeSorter;
	return (1);
}
