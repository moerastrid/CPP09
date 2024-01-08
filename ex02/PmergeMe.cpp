/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PmergeMe.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/04 18:02:38 by ageels        #+#    #+#                 */
/*   Updated: 2024/01/08 19:38:44 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

// LOSSE FUNCTIES
bool	isnumber(string str) {
	if (str.empty())
		return (false);
	for (string::iterator it = str.begin(); it != str.end(); it++) {
		if (isdigit(*it) == false)
			return (false);		
	}
	return (true);
}


// PRIVATE custom
bool	PmergeMe::parse(int argc, char **argv) {
	if (argc == 1)
		return (false);
	this->n = argc - 1;
	for (int i = 1; argv[i]; i++) {
		if (isnumber(argv[i]) == false)
			return(false);
		try {
			if (std::stol(argv[i]) > UINT_MAX)
				return (false);
			sequence.push_back(std::stol(argv[i]));
		} catch (std::out_of_range &ex) {
			return (false);
		}
	}
	return (true);
}

void	PmergeMe::run_vc() {
	auto start = std::chrono::high_resolution_clock::now();

	// data management part
	vector<uint>	vc(this->n);
	for(unsigned int i = 0; i < n; i++) {
		vc.push_back(sequence[n]);
	}

	// sorting part
	PmergeMe::sort(&vc);

	// more data management
	vc.clear();

	auto stop = std::chrono::high_resolution_clock::now();
	this->vc_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
}

void	PmergeMe::run_dc() {
	auto start = std::chrono::high_resolution_clock::now();

	// data management part
	deque<uint>	dc(this->n);
	for(unsigned int i = 0; i < n; i++) {
		dc.push_back(sequence[n]);
	}

	// sorting part
	PmergeMe::sort(&dc);

	// more data management
	dc.clear();

	auto stop = std::chrono::high_resolution_clock::now();
	this->dc_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
}


// PUBLIC ~ OCform
PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &src) {
	*this = src;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &src) {
	this->n = src.n;
	this->sequence = src.sequence;
	this->vc_time = src.vc_time;
	this->dc_time = src.dc_time;
	
	return (*this);
}


// PUBLIC getters/setters
unsigned int	PmergeMe::get_n() {
	return(this->n);
}

std::chrono::nanoseconds	PmergeMe::get_vc_time() {
	return(this->vc_time);
}

std::chrono::nanoseconds	PmergeMe::get_dc_time() {
	return(this->dc_time);
}

vector<uint>	PmergeMe::get_sequence() {
	return(this->sequence);
}


// PUBLIC custom
#include <algorithm>
void	PmergeMe::run(int argc, char **argv) {
	if (!parse(argc, argv))
		throw(PmergeMeException("ERROR: PARSE : Please enter a positive int sequence to sort"));
	run_vc();
	run_dc();
}

void	PmergeMe::sort(vector<uint> *vector_container) {
	std::sort(vector_container->begin(), vector_container->end());
}

void	PmergeMe::sort(deque<uint> *deque_container) {
	std::sort(deque_container->begin(), deque_container->end());
}


// ostream operator overload functions 
ostream 	&operator<<(ostream &o, const vector<uint> &src) {
	if (src.empty())
		return(o);
	for (auto it = src.begin(); it != src.end(); it++) {
		o << *it << " ";
	}
	return (o);
}

ostream 	&operator<<(ostream &o, deque<uint> &src) {
	if (src.empty())
		return(o);
	for (auto it = src.begin(); it != src.end(); it++) {
		o << *it << " ";
	}
	return (o);
}

ostream		&operator<<(ostream &o, PmergeMe &src) {
	vector<uint>	temp;	

	if (src.get_n() == 0) {
		o << "PmergeMe empty\n";
	} else {
		temp = src.get_sequence();
		o << "Before:\t" << temp << "\n";
		std::sort(temp.begin(), temp.end());
		o << "After:\t" << temp << "\n";
		o << "Time to process a range of " << src.get_n() << " with std::vector : " << src.get_vc_time().count() << "\n";
		o << "Time to process a range of " << src.get_n() << " with std::deque : " << src.get_dc_time().count() << "\n";
	}
	return (o);	
}
