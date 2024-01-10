/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PmergeMe.hpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/04 18:02:41 by ageels        #+#    #+#                 */
/*   Updated: 2024/01/10 18:14:46 by ageels        ########   odam.nl         */
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
#include <array>
#include <chrono>
#include <algorithm>
#include <climits>

bool	isnumber(string str);

class PmergeMe {
	private :
		unsigned int				n = 0;
		vector<uint>				sequence;
		std::chrono::nanoseconds	vc_time;
		std::chrono::nanoseconds	dc_time;
		vector<uint>				jacobssequence;

		struct	pair {
			unsigned int	large;
			unsigned int	small;
		};
	
		bool	parse(int argc, char **argv);
		void	calculate_jacobssequence(void);
		void	run_vc(void);
		void	run_dc(void);
		void	sort(vector<uint> &vc);
		void	sort(deque<uint> &dc);
		void	create_pairs(vector<PmergeMe::pair> &pairs, vector<uint> &vc);
		void	create_pairs(deque<PmergeMe::pair> &pairs, deque<uint> &dc);
		void	insert_elem(vector<uint> &vc, uint elem);
		void	insert_elem(deque<uint> &dc, uint elem);
		void	insert_elem(vector<PmergeMe::pair> &pairs, PmergeMe::pair elem);
		void	insert_elem(deque<PmergeMe::pair> &pairs, PmergeMe::pair elem);

	public :
		PmergeMe();
		~PmergeMe();
		PmergeMe(const PmergeMe &src);
		PmergeMe &operator=(const PmergeMe &src);

		unsigned int				get_n();
		std::chrono::nanoseconds	get_vc_time();
		std::chrono::nanoseconds	get_dc_time();
		vector<uint>				get_sequence();

		void	run(int argc, char **argv);

		class PmergeMeException : public logic_error {
			public :
				PmergeMeException(const string &message) : logic_error(message) {}
		};
};

ostream	&operator<<(ostream &o, const vector<uint> &src);
ostream	&operator<<(ostream &o, deque<uint> &src);
ostream	&operator<<(ostream &o, PmergeMe &src);