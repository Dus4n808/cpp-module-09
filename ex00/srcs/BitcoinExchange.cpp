/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 17:00:29 by dufama            #+#    #+#             */
/*   Updated: 2026/05/31 17:00:29 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/BitcoinExchange.hpp"
#include <cstddef>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <utility>

// ================================================================ //
// FCO                       
// ================================================================ //


// ===== Default Constructor =====
BitCoinExchange::BitCoinExchange() : _data() {}

// ===== Copy Constructor =====
BitCoinExchange::BitCoinExchange(const BitCoinExchange& copy) : _data(copy._data) {}

// ===== Overload =====
BitCoinExchange& BitCoinExchange::operator=(const BitCoinExchange& assign) {
	if (this != &assign) {
		_data = assign._data;
	}
	return *this;
}

// ===== Destructor =====
BitCoinExchange::~BitCoinExchange() {}

// ================================================================ //
// Methods                       
// ================================================================ //

// ===== Is Valide Date =====
bool BitCoinExchange::isValideDate(const std::string& date) const {
	if (date.length() != 10)
		return false;
	if (date[4] != '-' || date[7] != '-')
		return false;
	for (int i = 0; i < 10; ++i) {
		if (i == 4 || i == 7)
			continue;
		if (date[i] < '0' || date[i] > '9')
			return false;
	}
	std::string yearStr = date.substr(0, 4);
	std::string monthStr = date.substr(5, 2);
	std::string dayStr = date.substr(8, 2);

	int year, month, day;
	std::stringstream(yearStr) >> year;
	std::stringstream(monthStr) >> month;
	std::stringstream(dayStr) >> day;

	if (month < 1 || month > 12)
		return false;
	if (day < 1 || day > 31)
		return false;
	if (year < 2009 || year > 2024)
		return false;
	
	return true;
}

// ===== Trim =====

std::string BitCoinExchange::trim(const std::string& str) const {
	std::string whiteSpace = " \t\n\r";
	size_t start = str.find_first_not_of(whiteSpace);
	if (start == std::string::npos)
		return "";
	size_t end = str.find_last_not_of(whiteSpace);
	return str.substr(start, end - start + 1);
}

// ===== LoadDataBase =====

void BitCoinExchange::loadDataBase(const std::string& filename) {
	std::ifstream file(filename.c_str());
	if (!file.is_open())
		throw ErrorFile();
	
	std::string line;
	std::getline(file, line);
	size_t numberOfline = 0;
	while (std::getline(file, line)) {
		line = trim(line);
		if (line.empty())
			continue;
		size_t pos = line.find(',');
		if (pos == std::string::npos)
			throw ErrorFile();
		std::string date = trim(line.substr(0, pos));
		std::string value = trim(line.substr(pos + 1));
		if (!isValideDate(date))
			throw ErrorFile();

		// ===== Conversion =====
		double v;
		std::stringstream ss(value);
		ss >> v;
		if (ss.fail() || !ss.eof())
			throw ErrorFile();
		numberOfline++;
		_data.insert(std::pair<std::string, double>(date, v));
	}
	if (numberOfline != _data.size())
		throw ErrorFile();
}

// ===== Read Input File =====

void BitCoinExchange::readInputFile(const std::string& filename) {
	std::ifstream file(filename.c_str());
	if (!file.is_open())
		throw ErrorFile();

	std::string line;
	std::getline(file, line);
	while (std::getline(file, line)) {
		line = trim(line);
		if (line.empty())
			continue;
		size_t pos = line.find('|');
		if (pos == std::string::npos) {
			std::cerr << "Error : bad input => " << line << std::endl; 
			continue;
		}
		std::string date = trim(line.substr(0, pos));
		std::string value = trim(line.substr(pos + 1));
		if (!isValideDate(date)) {
			std::cerr << "Error : date invalid => " << line << std::endl;
			continue;
		}
		double v;
		std::stringstream ss(value);
		ss >> v;
		if (ss.fail() || !ss.eof()) {
			std::cerr << "Error de conversion" << std::endl;
			continue;
		}
		if (v < 0) {
			std::cerr << "Error : not a positive number." << std::endl;
			continue;
		}
		if (v > 1000) {
			std::cerr << "Error : too large number." << std::endl;
			continue;
		}
		std::cout << date << " lol " << v << std::endl;
	}
}

void BitCoinExchange::readMap() {
	std::map<std::string, double>::iterator it;
	for (it = _data.begin(); it != _data.end(); ++it) {
		std::cout << it->first << "  " << it->second << std::endl;
	}
}