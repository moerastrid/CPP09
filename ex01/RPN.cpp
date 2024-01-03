/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   RPN.cpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/03 13:09:30 by ageels        #+#    #+#                 */
/*   Updated: 2024/01/03 13:46:37 by ageels        ########   odam.nl         */
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

const stack<int>	RPN::getStorage() {
	return (this->storage);
}

ostream 	&operator<<(ostream &o, RPN &src) {
	stack<int>tempstack = src.getStorage();
	while(!tempstack.empty()) {
		o << tempstack.top() << " ";
		tempstack.pop();
	}
	return (o);
}