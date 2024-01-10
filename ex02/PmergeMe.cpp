/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PmergeMe.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/04 18:02:38 by ageels        #+#    #+#                 */
/*   Updated: 2024/01/10 13:42:23 by ageels        ########   odam.nl         */
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
	vector<uint>	vc;

	vc.reserve(this->n);
	for(unsigned int i = 0; i < n; i++) {
		vc.push_back(sequence[i]);
	}

	// sorting part << "\x1B[34mRPN - " << str << "\x1B[0m\n";
	cout << "\x1B[34mVC bc :" << vc << "\x1B[0m\n";
	PmergeMe::sort(vc);
	cout << "\x1B[34mVC ad :" << vc << "\x1B[0m\n";

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
	run_vc();
	run_dc();
}

// create the PmergeMe pairs and put the right elem in either large or small
vector<PmergeMe::pair>	PmergeMe::create_pairs(vector<uint> &vc) {
	vector<PmergeMe::pair>	pairs;
	pairs.reserve(vc.size() / 2);
	
	unsigned int i = 0;
	for (auto it = vc.begin(); it != vc.end(); it++) {
		if (i % 2 == 0) {
			pair new_pair;
			new_pair.small = (*it < *(it + 1) ? *it : *(it + 1));
			new_pair.large = (*it > *(it + 1) ? *it : *(it + 1));
			cout << "pair " << i / 2 << "\tsmall: " << new_pair.small << "\tlarge: " << new_pair.large << "\n";
			pairs.push_back(new_pair);
		}
		i++;
	}
	return (pairs);
}

// insert element at the right place
void	PmergeMe::insert_elem(vector<PmergeMe::pair> &pairs, PmergeMe::pair to_be_inserted, size_t n) {
	for (int i = n - 2; i >= 0; i--) {
		if ((pairs[i]).large > to_be_inserted.large) {
			pairs[i+1] = pairs[i];
		} else {
			pairs[i+1]  = to_be_inserted;
			break;
		}
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

// recursive insertion sort pairs
void	PmergeMe::sort_pairs(vector<PmergeMe::pair> &pairs, size_t n) {
	if (n <= 1)
		return ;
	
	sort_pairs(pairs, n - 1);
	insert_elem(pairs, pairs[n - 1], n);
}

// sort the elements inside the vector
void	PmergeMe::sort(vector<uint> &vc) {
	bool						uneven = false;
	unsigned int				last = 0;

	cout << "incoming: " << vc << "\n";

	if (n % 2 != 0) {
		uneven = true;
		last = vc.at(n - 1);
		vc.pop_back();
		cout << "modified: " << vc << "\n";
	}
	
	if (uneven == true) {
		cout << "BEWARE - uneven ! " << last << "\n";
	}

	vector<PmergeMe::pair>	pairs = create_pairs(vc);

	cout << "pairs (bc):\n";
	for (auto it = pairs.begin(); it != pairs.end(); it++) {
		cout << "\tsmall: " << (*it).small << "\tlarge: " << (*it).large << "\n";
	}
	
	sort_pairs(pairs, pairs.size());

	// now make the large elems the main chain
	vc.clear();
	cout << "pairs (ad):\n";
	for (auto it = pairs.begin(); it != pairs.end(); it++) {
		vc.push_back((*it).large);
		cout << "\tsmall: " << (*it).small << "\tlarge: " << (*it).large << "\n";
	}
	
	// now put the small elements back inside from pairs to main chain
	//insert_elem(vc, )
	
	
	// then put the last one there too

	if (uneven == true) {
		insert_elem(vc, last);
	}

	cout << "modified: " << vc << "\n";
}

// sort the elements inside the deque
void	PmergeMe::sort(deque<uint> *dc) {
	std::sort(dc->begin(), dc->end());
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
