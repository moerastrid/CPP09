/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   BitcoinExchange.hpp                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/25 13:51:35 by ageels        #+#    #+#                 */
/*   Updated: 2023/09/25 15:31:53 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>

class BitcoinExchange {
	private :
		message(const std::string str)

	public :
		BitcoinExchange();									// default constructor
		~BitcoinExchange();									// default destructor
		BitcoinExchange(const BitcoinExchange &src);				// copy constructor
		BitcoinExchange &operator=(const BitcoinExchange &src);	// assignment operator
};

std::ostream 	&operator<<(std::ostream &o, BitcoinExchange &src);