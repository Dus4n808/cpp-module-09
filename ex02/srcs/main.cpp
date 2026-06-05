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

int main(int ac, char *av[]) {
	PmergeMe a;

	std::string b = "34";
	try {
		for (int i = 1; i < ac; ++i) {
			std::string arg(av[i]);
			a.test(arg);
		}
	}
	catch (std::exception& e) {
		std::cerr << "Error : " << e.what() << std::endl;
	}
	return 0;
}