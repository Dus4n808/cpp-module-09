/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 14:40:43 by dufama            #+#    #+#             */
/*   Updated: 2026/05/31 14:40:43 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <exception>
#include <map>
#include <string>


class BitCoinExchange {
	private:
		std::map<std::string, double> _data;
		double getRate(double value, std::string& date);
	
	public:
		// ===== FCO =====
		BitCoinExchange();
		BitCoinExchange(const BitCoinExchange& copy);
		BitCoinExchange& operator=(const BitCoinExchange& assign);
		~BitCoinExchange();
		void loadDataBase(const std::string& filename);
		void readInputFile(const std::string& filename);

		// ===== Exception =====
		class ErrorFile : public std::exception {
			public:
				virtual const char * what() const throw() {
					return "Error: could not open file.";
				}
		};
};

#endif