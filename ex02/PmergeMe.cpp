/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PmergeMe.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/04 18:02:38 by ageels        #+#    #+#                 */
/*   Updated: 2024/01/10 18:25:24 by ageels        ########   odam.nl         */
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

void	PmergeMe::calculate_jacobssequence(void) {
	vector<uint>	og_jaboc_sequence = {0, 1}; 
	unsigned int	amount = (this->n / 2);
	
	while (*(og_jaboc_sequence.end() - 1) < amount) {
		unsigned int	jacobsthal_number = (*(og_jaboc_sequence.end() - 1)) + 2 * (*(og_jaboc_sequence.end() - 2));
		og_jaboc_sequence.push_back(jacobsthal_number);
	}

	jacobssequence.push_back(1);

	for (auto it = og_jaboc_sequence.begin(); it != og_jaboc_sequence.end(); it++) {
		uint current = jacobssequence[jacobssequence.size() - 1];
		
		if (*it < current)
			continue ;
		if (*it > current)
		{
			for (uint new_number = *it; new_number > *(it - 1); new_number--)
				if (new_number < amount)
					jacobssequence.push_back(new_number);
		}
	}
}


void	PmergeMe::run_vc() {
	auto start = std::chrono::high_resolution_clock::now();

	// data management part
	vector<uint>	vc;

	vc.reserve(this->n);
	for(unsigned int i = 0; i < n; i++) {
		vc.push_back(sequence[i]);
	}

	// sorting part
	if (n > 1)
		PmergeMe::sort(vc);


	// more data management
	vc.clear();

	auto stop = std::chrono::high_resolution_clock::now();
	this->vc_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
}

void	PmergeMe::run_dc() {
	auto start = std::chrono::high_resolution_clock::now();

	// data management part
	deque<uint>	dc;
	for(unsigned int i = 0; i < n; i++) {
		dc.push_back(sequence[i]);
		
	}

	if (n > 1)
		PmergeMe::sort(dc);

	// more data management
	dc.clear();

	auto stop = std::chrono::high_resolution_clock::now();
	this->dc_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
}


// sort the elements inside the vector
void	PmergeMe::sort(vector<uint> &vc) {
	vector<PmergeMe::pair>	pairs;
	bool					uneven = false;
	unsigned int			last = 0;

	if (n % 2 != 0) {
		uneven = true;
		last = vc.at(n - 1);
		vc.pop_back();
	}
	create_pairs(pairs, vc);
	vc.clear();
	for (auto it = pairs.begin(); it != pairs.end(); it++) {
		vc.push_back((*it).large);
	}
	vc.insert(vc.begin(), (pairs[0]).small);

	for (size_t i = 0; i < pairs.size() - 1; i++) {
		size_t pos = jacobssequence[i];
		insert_elem(vc, (pairs[pos]).small);
	}
	if (uneven == true) {
		insert_elem(vc, last);
	}
}

// sort the elements inside the deque
void	PmergeMe::sort(deque<uint> &dc) {
	deque<PmergeMe::pair>	pairs;
	bool					uneven = false;
	unsigned int			last = 0;

	if (n % 2 != 0) {
		uneven = true;
		last = dc.at(n - 1);
		dc.pop_back();
	}
	create_pairs(pairs, dc);
	dc.clear();
	for (auto it = pairs.begin(); it != pairs.end(); it++) {
		dc.push_back((*it).large);
	}
	dc.push_front((pairs[0]).small);
	
	for (size_t i = 0; i < pairs.size() - 1; i++) {
		size_t pos = jacobssequence[i];
		insert_elem(dc, (pairs[pos]).small);
	}
	if (uneven == true) {
		insert_elem(dc, last);
	}
}

// create the PmergeMe pairs
// inside the pair: put the right elem in either large or small
// in the pair array : insert elem at the right place (recursive insertion sort)
void	PmergeMe::create_pairs(vector<PmergeMe::pair> &pairs, vector<uint> &vc) {
	pairs.reserve(vc.size() / 2);
	
	unsigned int i = 0;
	for (auto it = vc.begin(); it != vc.end(); it++) {
		if (i % 2 == 0) {
			pair new_pair;
			new_pair.small = (*it < *(it + 1) ? *it : *(it + 1));
			new_pair.large = (*it > *(it + 1) ? *it : *(it + 1));
			insert_elem(pairs, new_pair);
		}
		i++;
	}
}

// create the PmergeMe pairs
// inside the pair: put the right elem in either large or small
// in the pair array : insert elem at the right place (recursive insertion sort)
void	PmergeMe::create_pairs(deque<PmergeMe::pair> &pairs, deque<uint> &dc) {
	unsigned int i = 0;
	for (auto it = dc.begin(); it != dc.end(); it++) {
		if (i % 2 == 0) {
			pair new_pair;
			new_pair.small = (*it < *(it + 1) ? *it : *(it + 1));
			new_pair.large = (*it > *(it + 1) ? *it : *(it + 1));
			insert_elem(pairs, new_pair);
		}
		i++;
	}
}

// insert element at the right place
void	PmergeMe::insert_elem(vector<uint> &vc, uint elem) {
	for (auto it = vc.begin(); it != vc.end(); it++) {
		if (elem <= *it) {
			vc.insert(it, elem);
			return;
		}
	}
	vc.push_back(elem);
}

// insert element at the right place
void	PmergeMe::insert_elem(deque<uint> &dc, uint elem) {
	for (auto it = dc.begin(); it != dc.end(); it++) {
		if (elem <= *it) {
			dc.insert(it, elem);
			return;
		}
	}
	dc.push_back(elem);
}

// insert element at the right place
void	PmergeMe::insert_elem(vector<PmergeMe::pair> &pairs, PmergeMe::pair elem) {
	for (auto it = pairs.begin(); it != pairs.end(); it++) {
		if (elem.large <= (*it).large) {
			pairs.insert(it, elem);
			return;
		}
	}
	pairs.push_back(elem);
}

// insert element at the right place
void	PmergeMe::insert_elem(deque<PmergeMe::pair> &pairs, PmergeMe::pair elem) {
	for (auto it = pairs.begin(); it != pairs.end(); it++) {
		if (elem.large <= (*it).large) {
			pairs.insert(it, elem);
			return;
		}
	}
	pairs.push_back(elem);
}


// PUBLIC ~ OCform
PmergeMe::PmergeMe() {
}

PmergeMe::~PmergeMe() {
}

PmergeMe::PmergeMe(const PmergeMe &src) {
	*this = src;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &src) {
	this->n = src.n;
	this->sequence = src.sequence;
	this->jacobssequence = src.jacobssequence;
	this->vc_time = src.vc_time;
	this->dc_time = src.dc_time;
	return (*this);
}


// PUBLIC getters/setters
// get number of elements
unsigned int	PmergeMe::get_n() {
	return(this->n);
}

// get the time it takes to sort vector container
std::chrono::nanoseconds	PmergeMe::get_vc_time() {
	return(this->vc_time);
}

// get the time it takes to sort deque container
std::chrono::nanoseconds	PmergeMe::get_dc_time() {
	return(this->dc_time);
}

// get the original unsorted sequence
vector<uint>	PmergeMe::get_sequence() {
	return(this->sequence);
}


// PUBLIC custom
// run the program PmergeMe at the sequence
void	PmergeMe::run(int argc, char **argv) {
	if (!parse(argc, argv))
		throw(PmergeMeException("ERROR: PARSE : Please enter a positive int sequence to sort"));
	calculate_jacobssequence();
	run_vc();
	run_dc();
}


// ostream operator OVERLOAD FUNCTIONS
// print vector
ostream 	&operator<<(ostream &o, const vector<uint> &src) {
	if (src.empty())
		return(o);
	for (auto it = src.begin(); it != src.end(); it++) {
		o << *it << " ";
	}
	return (o);
}

//print deque
ostream 	&operator<<(ostream &o, deque<uint> &src) {
	if (src.empty())
		return(o);
	for (auto it = src.begin(); it != src.end(); it++) {
		o << *it << " ";
	}
	return (o);
}

// print PmergeMe
ostream		&operator<<(ostream &o, PmergeMe &src) {
	vector<uint>	temp;	

	if (src.get_n() == 0) {
		o << "PmergeMe empty\n";
	} else {
		temp = src.get_sequence();
		o << "Before:\t";
		if (temp.size() <= 5) {
			o << temp << "\n";
		} else {
			for (int i = 0; i < 4; i++) {
				o << temp[i] << " ";
			}
			o << "[...]\n";
		}
		std::sort(temp.begin(), temp.end());
		o << "After:\t";
		if (temp.size() <= 5) {
			o << temp << "\n";
		} else {
			for (int i = 0; i < 4; i++) {
				o << temp[i] << " ";
			}
			o << "[...]\n";
		}
		o << "Time to process a range of " << src.get_n() << " with std::vector :\t" << src.get_vc_time().count() << " nanoseconds\n";
		o << "Time to process a range of " << src.get_n() << " with std::deque :\t" << src.get_dc_time().count() << " nanoseconds\n";
	}
	return (o);	
}
