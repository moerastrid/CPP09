/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   BitcoinExchange.hpp                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/25 13:51:35 by ageels        #+#    #+#                 */
/*   Updated: 2023/11/08 13:07:30 by astrid        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <map>

class BitcoinExchange {
	private :
		void		message(const std::string str);
		// std::map,	dataMap;

	public :
		BitcoinExchange();											// default constructor
		~BitcoinExchange();											// default destructor
		BitcoinExchange(const BitcoinExchange &src);				// copy constructor
		BitcoinExchange	&operator=(const BitcoinExchange &src);		// assignment operator
};

std::ostream	&operator<<(std::ostream &o, BitcoinExchange &src);		