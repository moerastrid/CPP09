/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PmergeMe.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/04 18:02:38 by ageels        #+#    #+#                 */
/*   Updated: 2024/01/04 21:42:36 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"


// public ~ OCform
PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &src) {
	*this = src;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &src) {
	(void)src;
	return (*this);
}

// PUBLIC custom
#include <algorithm>
void	PmergeMe::sort(vector<uint> *vector_container) {
	std::sort(vector_container->begin(), vector_container->end());
}

void	PmergeMe::sort(deque<uint> *deque_container) {
	std::sort(deque_container->begin(), deque_container->end());
}


// ostream operator overload functions 
ostream 	&operator<<(ostream &o, vector<uint> &src) {
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