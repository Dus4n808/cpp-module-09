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

#include <cstdlib>
#include <exception>
#include <string>
#include <iostream>
#include "../headers/BitcoinExchange.hpp"


int main(int argc, char *argv[]) {
	if (argc != 2) {
		std::cout << "Usage: ./btc [file]" << std::endl;	
	}
	else {
		BitCoinExchange a;
		try {
			a.loadDataBase("test.csv");
		}
		catch (std::exception& e) {
			std::cerr << "Error : " << e.what() << std::endl;
			std::cerr << "Please enter a valid database" << std::endl;
			return EXIT_FAILURE;
		}
		try {
			a.readInputFile(argv[1]);
		}
		catch (std::exception& e) {
			std::cerr << "Error : " << e.what() << std::endl;
			std::cerr << "Please add a valid input file (./btc [input file])" << std::endl;
		}
	}
	return 0;
}