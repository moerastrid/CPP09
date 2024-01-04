/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   RPN.cpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/03 13:09:30 by ageels        #+#    #+#                 */
/*   Updated: 2024/01/04 16:23:48 by ageels        ########   odam.nl         */
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
void	RPN::message(const std::string str) {
	//cout << "\x1B[34mRPN - " << str << "\x1B[0m\n";
	(void)str;
}

void	RPN::message(char ch, const std::string str) {
	//cout << "\x1B[34mRPN - " << ch << str << "\x1B[0m\n";	
	(void)ch;
	(void)str;
}

void	RPN::operation(char ch) {
	int n1;
	int n2;

	if (storage.size() < 2) {
		throw (RPNException("Error: operation not possible"));
	}
	n1 = storage.top();
	storage.pop();
	n2 = storage.top();
	storage.pop();

	switch (ch) {
		case '+' :
			storage.push(n2 + n1);
			break;
		case '-' :
			storage.push(n2 - n1);
			break;
		case '*' :
			storage.push(n2 * n1);
			break;
		case '/' :
			storage.push(n2 / n1);
			break;
		default :
			throw (RPNException("impossible error?!"));
	}
}

void	RPN::digit(char ch) {
	int n = ch - '0';
	storage.push(n);
}


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
	message("Analyzing ... " + input + " ...");
	
	for(string::iterator it = input.begin(); it != input.end(); it++) {
		switch (*it) {
			case ' ' : case '\t' : case '\r' : case '\n' : case '\f' : case '\v' :
				break ;
			case '0' ... '9' :
				message(*it, " is digit");
				digit(*it);
				break ;			// operations
			case '-': case '+' : case '*' : case '/' :
				message(*it, "is operation");
				operation(*it);
				break;
			default :
				throw (RPNException("invalid input"));
		}
	}
	
	message("Calculating ..." + input + "...");
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
