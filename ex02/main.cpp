/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/04 18:02:34 by ageels        #+#    #+#                 */
/*   Updated: 2024/01/04 21:38:54 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
	using std::cout;
	using std::cerr;
#include <vector>
	using std::vector;
#include <deque>
	using std::deque;
#include <string>
	using std::string;
#include <chrono>

#include "PmergeMe.hpp"

static bool	isnumber(string str) {
	if (str.empty())
		return (false);
	for (string::iterator it = str.begin(); it != str.end(); it++) {
		if (isdigit(*it) == false)
			return (false);		
	}
	return (true);
}

static bool	parse(int argc, char **argv, vector<int> *vc, deque<int> *dc) {
	if (argc == 1) {
		cerr << "Please enter an int sequence to sort\n";
		return (false);
	}
	for (int i = 1; argv[i]; i++) {
		if (isnumber(argv[i]) == false) {
			cerr << "Please enter an int sequence to sort\n";
			return(false);
		} else {
			vc->push_back(std::stoi(argv[i]));
			dc->push_back(std::stoi(argv[i]));
		}
	}

	return (true);
}


int main(int argc, char **argv) {
	PmergeMe	PMergeSorter;
	vector<int>	vector_container;
	deque<int>	deque_container;

	if (!parse(argc, argv, &vector_container, &deque_container))
		return (-1);
	
	// process vector
	cout << "\nvector before: " << vector_container << "\n";
	auto vc_start = std::chrono::high_resolution_clock::now();
	try {
		PMergeSorter.sort(&vector_container);
	} catch (const PmergeMe::PmergeMeException &ex) {
		cerr << "\x1B[31m" << ex.what() << "\x1B[0m" << std::endl;		
	}
	auto vc_stop = std::chrono::high_resolution_clock::now();
	auto vc_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(vc_stop - vc_start);
	cout << "vector after: " << vector_container << "\n";
	cout << "vector duration: " << vc_duration.count() << " nanoseconds\n";

	// process deque
	cout << "\ndeque before: " << deque_container << "\n";
	auto dc_start = std::chrono::high_resolution_clock::now();
	try {
		PMergeSorter.sort(&deque_container);
	} catch (const PmergeMe::PmergeMeException &ex) {
		cerr << "\x1B[31m" << ex.what() << "\x1B[0m" << std::endl;		
	}
	auto dc_stop = std::chrono::high_resolution_clock::now();
	auto dc_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(dc_stop - dc_start);
	cout << "deque after: " << deque_container << "\n";
	cout << "deque duration: " << dc_duration.count() << " nanoseconds\n";
	return (1);
}
