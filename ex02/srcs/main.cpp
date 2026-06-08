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
#include <exception>
#include <iostream>
#include <string>

std::string concat(int argc, char *argv[]) {
	std::string input;
	for (int i = 1; i < argc; ++i) {
		if (i > 1)
			input += " ";
		input += argv[i];
	}
	return input;
}

int main(int ac, char *av[]) {
	PmergeMe a;

	std::string input = concat(ac, av);
	try {
		a.sort(input);
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}