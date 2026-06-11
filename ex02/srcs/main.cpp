/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 15:56:16 by dufama            #+#    #+#             */
/*   Updated: 2026/06/05 15:56:16 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/PmergeMe.hpp"
#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>



static std::string concat(int argc, char *argv[]) {
	std::string input;
	for (int i = 1; i < argc; ++i) {
		if (i > 1)
			input += " ";
		input += argv[i];
	}
	return input;
}

int main(int argc, char *argv[]) {
	PmergeMe a;

	if (argc < 2) {
		std::cerr << "Usage : ./PmergeMe [Numbers input]" << std::endl;
	}
	else {
		std::string input = concat(argc, argv);
		try {
			a.sort(input);
		}
		catch (std::exception& e) {
			std::cerr << "Error : " << e.what() << std::endl;
			return EXIT_FAILURE;
		}
	}
	return 0;
}