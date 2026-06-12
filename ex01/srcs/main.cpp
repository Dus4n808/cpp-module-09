/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 10:24:15 by dufama            #+#    #+#             */
/*   Updated: 2026/06/05 10:24:15 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/RPN.hpp"
#include <cstddef>
#include <exception>
#include <iostream>
#include <ostream>
#include <string>

void testMandatory(void) {
	std::string a = "8 9 * 9 - 9 - 9 - 4 - 1 +";
	std::string b = "7 7 * 7 -";
	std::string c = "1 2 * 2 / 2 * 2 4 - +";
	std::string d = "(1 + 1)";
	std::string tab[] = {a, b, c, d};

	for (size_t i = 0; i < 4; ++i) {
		try {
			RPN tester;
			std::cout << tester.solve(tab[i]) << std::endl;
		}
		catch (std::exception& e) {
			std::cerr << "Error : " << e.what() << std::endl;
		}
	}
}

void myTest(void) {
	std::string a = "    1 + 1 ";
	std::string b = "  3 1   + 1 +";
	std::string c = "1 2 3 + +";
	std::string d = "coucou1+";
	std::string e = " 2   3 *";
	std::string f = " 0  1 /";
	std::string tab[] = {a, b, c, d, e, f};

	for (size_t i = 0; i < 6; ++i) {
		try {
			RPN tester;
			std::cout << tester.solve(tab[i]) << std::endl;
		}
		catch (std::exception& e) {
			std::cerr << "Error : " << e.what() << std::endl;
		}
	}
}

int main(int argc, char *argv[]) {
	RPN genius;
	
	if (argc == 2) {
		std::cout << std::endl << "===== Input User =====" << std::endl << std::endl;
		try {
			std::cout << genius.solve(argv[1]) << std::endl;
		}
		catch (std::exception& e) {
			std::cerr << "Error : " << e.what() << std::endl;
		}
		std::cout << std::endl << "===== Mandatory test =====" << std::endl << std::endl;
		testMandatory();
		std::cout << std::endl << "===== My test =====" << std::endl << std::endl;
		myTest();
	}
	else {
		std::cerr << "Usage: ./RPM [1 1 +]" << std::endl;
		return 1;
	}
	return 0;
}