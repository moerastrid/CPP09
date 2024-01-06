/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PmergeMe.hpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/04 18:02:41 by ageels        #+#    #+#                 */
/*   Updated: 2024/01/06 19:35:42 by astrid        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
	using std::ostream;
	using std::cout;
#include <stdexcept>
	using std::logic_error;
#include <string>
	using std::string;
#include <vector>
	using std::vector;
#include <deque>
	using std::deque;
#include <climits>

class PmergeMe {
	private :
		unsigned int	n_elem;

	public :
		PmergeMe();
		~PmergeMe();
		PmergeMe(const PmergeMe &src);
		PmergeMe &operator=(const PmergeMe &src);

		void	sort(vector<uint> *vector_container);
		void	sort(deque<uint> *deque_container);

		class PmergeMeException : public logic_error {
			public :
				PmergeMeException(const string &message) : logic_error(message) {}
		};
};

ostream	&operator<<(ostream &o, vector<uint> &src);
ostream	&operator<<(ostream &o, deque<uint> &src);