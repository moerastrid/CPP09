/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   BitcoinExchange.hpp                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/25 13:51:35 by ageels        #+#    #+#                 */
/*   Updated: 2024/01/02 14:41:17 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <string>


class BitcoinExchange {
	private :
		std::map<std::string, int>	dataMap;

		void						message(const std::string str);

	public :
		BitcoinExchange();											// default constructor
		~BitcoinExchange();											// default destructor
		BitcoinExchange(const BitcoinExchange &src);				// copy constructor
		BitcoinExchange	&operator=(const BitcoinExchange &src);		// assignment operator

		bool		setDB();
		std::string	exchange(std::string input);
		void		verifyInput(std::string input);
			
		class BitcoinExchangeException : public std::logic_error {
		public:
			BitcoinExchangeException(const std::string& message) : std::logic_error(message) {}
		};
};

std::ostream	&operator<<(std::ostream &o, BitcoinExchange &src);