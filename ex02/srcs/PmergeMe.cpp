/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 15:25:16 by dufama            #+#    #+#             */
/*   Updated: 2026/06/05 15:25:16 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/PmergeMe.hpp"
#include <deque>
#include <limits>
#include <sstream>
#include <iostream>
#include <vector>

// ================================================================ //
// FCO                       
// ================================================================ //


// ===== Default Constructor =====
PmergeMe::PmergeMe() : _vector(), _deque() {}

// ===== Copy Constructor =====
PmergeMe::PmergeMe(const PmergeMe& copy) : _vector(copy._vector), _deque(copy._deque) {}

// ===== Overload =====
PmergeMe& PmergeMe::operator=(const PmergeMe& assign) {
	if (this != &assign) {
		_deque = assign._deque;
		_vector = assign._vector;
	}
	return *this;
}

// ===== Destructor =====
PmergeMe::~PmergeMe() {}

// ================================================================ //
// Methods                       
// ================================================================ //

void PmergeMe::fill(const std::string& str) {

	std::vector<int> tmp;
	std::istringstream ss(str);
	long value;
	
	while (ss >> value) {
		if (value < 0)
			throw NumebrError();
		if (value > std::numeric_limits<int>::max())
			throw Overflow();
		tmp.push_back(static_cast<int>(value));
	}
	if (!ss.eof() && ss.fail())
		throw BadInput();

	_vector = tmp;
	_deque.assign(tmp.begin(), tmp.end());
}

static void printDeque(const std::deque<int>& d) {
	std::deque<int>::const_iterator it;
	for (it = d.begin(); it != d.end(); ++it) {
		std::cout << *it << std::endl;
	}
}

void PmergeMe::test(std::string& str) {
	fill(str);
	printDeque(_deque);
}