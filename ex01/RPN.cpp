/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   RPN.cpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/03 13:09:30 by ageels        #+#    #+#                 */
/*   Updated: 2024/01/04 13:33:59 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

// public ~ OCform
RPN::RPN() {
}

RPN::~RPN() {}

RPN::RPN(const RPN &src) {
	*this = src;
}

RPN &RPN::operator=(const RPN &src) {
	this->storage = src.storage;
	return (*this);
}

// PRIVATE custom




// PUBLIC get/set

const stack<int>	RPN::getStorage() {
	return (this->storage);
}

void	RPN::reset(void) {
	while (!this->storage.empty()) {
		storage.pop();
	}
}


// PUBLIC custom

void	RPN::calculate(string input) {
	cout << "Analyzing ..." << input << "...\n";
	
	for(string::iterator it = input.begin(); it != input.end(); it++) {
		switch (*it) {
			// white space characters
			case ' ' : case '\t' : case '\r' : case '\n' : case '\f' : case '\v' :
				break ;
			// digits
			case '0' ... '9' :
				cout << *it << " is number\n";
				break ;
			// operations
			case '-': case '+' : case '*' : case '/' :
				cout << *it << " is operation\n";
				break;
			// anything else (error)
			default :
				throw (RPNException("invalid input"));
		}
	}
	
	
	cout << "Calculating ..." << input << "...\n";
	this->storage.push(6);
}


// STREAM OVERLOAD

ostream 	&operator<<(ostream &o, RPN &src) {
	stack<int>tempstack = src.getStorage();
	if (tempstack.empty()) {
		o << "nothing in store";
		return(o);
	}
	while(!tempstack.empty()) {
		o << tempstack.top() << " ";
		tempstack.pop();
	}
	return (o);
}
