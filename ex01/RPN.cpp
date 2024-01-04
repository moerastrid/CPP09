/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   RPN.cpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/03 13:09:30 by ageels        #+#    #+#                 */
/*   Updated: 2024/01/04 16:39:43 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

//LOCAL
static void	debugmessage(const string str) {
	//cout << "\x1B[34mRPN - " << str << "\x1B[0m\n";
	(void)str;
}

static void	debugmessage(char ch, const string str) {
	//cout << "\x1B[34mRPN - " << ch << str << "\x1B[0m\n";	
	(void)ch;
	(void)str;
}

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
	debugmessage("Analyzing ... " + input + " ...");
	
	for(string::iterator it = input.begin(); it != input.end(); it++) {
		switch (*it) {
			case ' ' : case '\t' : case '\r' : case '\n' : case '\f' : case '\v' :
				break ;
			case '0' ... '9' :
				debugmessage(*it, " is digit");
				digit(*it);
				break ;			// operations
			case '-': case '+' : case '*' : case '/' :
				debugmessage(*it, "is operation");
				operation(*it);
				break;
			default :
				throw (RPNException("invalid input"));
		}
	}
	
	debugmessage("Calculating ..." + input + "...");
}


// STREAM OVERLOAD

ostream 	&operator<<(ostream &o, RPN &src) {
	stack<int>tempstack = src.getStorage();
	if (tempstack.empty()) {
		debugmessage("nothing in store");
		return(o);
	}
	while(!tempstack.empty()) {
		o << tempstack.top() << " ";
		tempstack.pop();
	}
	return (o);
}
