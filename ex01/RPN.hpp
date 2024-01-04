/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   RPN.hpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/03 13:09:21 by ageels        #+#    #+#                 */
/*   Updated: 2024/01/04 13:15:29 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <stack>
	using std::stack;
#include <iostream>
	using std::ostream;
	using std::cout;
#include <string>
	using std::string;

// RPN stands for reversed polish notation, aka postfix notation.
class RPN {
	private :
		stack<int>	storage;

	public :
		RPN();							//default constructor
		~RPN();							//default destructor
		RPN(const RPN &src);			//copy constructor
		RPN &operator=(const RPN &src);	//= sign operator

		const stack<int>	getStorage();
		void	reset(void);
	
		void	calculate(string input);
		
		class RPNException : public std::logic_error {
			public :
				RPNException(const string &message) : std::logic_error(message) {}
		};
};

ostream	&operator<<(ostream &o, RPN &src);
