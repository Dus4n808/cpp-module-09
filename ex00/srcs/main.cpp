/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 16:46:42 by dufama            #+#    #+#             */
/*   Updated: 2026/05/31 16:46:42 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exception>
#include <map>
#include <string>
#include <iostream>
#include "../headers/BitcoinExchange.hpp"


int main() {
	// std::map<std::string, int> a;
	// a.insert(std::pair<std::string, int>("coucou", 12));

	// std::map<std::string, int>::iterator it;

	// for (it = a.begin(); it != a.end(); ++it) {
	// 	std::cout << it->first << it->second << srs 
	// }
	BitCoinExchange a;
	try {
		a.loadDataBase("data.csv");
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	try {
		a.readInputFile("input.txt");
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	// a.readMap();
	return 0;
}