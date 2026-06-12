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
#include <cctype>
#include <cstddef>
#include <ctime>
#include <deque>
#include <limits>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <sys/time.h>

// ================================================================ //
// Utils                       
// ================================================================ //


// ===== Generator JacobSthal (Utils) =====

std::vector<size_t> jacobSthal(size_t maxIndex) {
	std::vector<size_t> jacob;
	jacob.push_back(0);
	jacob.push_back(1);

	size_t last = 0;
	size_t prev = 1;

	while (true) {
		size_t next = last + 2 * prev;
		jacob.push_back(next);
		prev = last;
		last = next;
		if (next > maxIndex)
			break;
	}
	return jacob;
}

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


// ===== Check value and fill container =====
void PmergeMe::_checkInputAndFillContainer(const std::string& str) {

	std::vector<int> tmp;
	std::istringstream ss(str);
	std::string token;
	
	while (ss >> token) {
		for (size_t i = 0; i < token.size(); ++i) {
			if (!std::isdigit(static_cast<unsigned char>(token[i])))
				throw BadInput();
		}
		std::istringstream conv(token);
		long value;
		conv >> value;
		if (conv.fail())
			throw Overflow();
		if (value > std::numeric_limits<int>::max())
			throw Overflow();
		tmp.push_back(static_cast<int>(value));
	}
	if (tmp.empty())
		throw BadInput();

	_vector = tmp;
	_deque.assign(tmp.begin(), tmp.end());
}

double PmergeMe::_sortVector() {
	clock_t start = clock();
	_vector = fordJohnsonSort(_vector);
	clock_t end = clock();
	double timeInterval = (end - start) * 1000000.0 / CLOCKS_PER_SEC;
	return timeInterval;
}

double PmergeMe::_sortDeque() {
	clock_t start = clock();
	_deque = fordJohnsonSort(_deque);
	clock_t end = clock();
	double timeInterval = (end - start) * 1000000.0 / CLOCKS_PER_SEC;
	return timeInterval;
}

void PmergeMe::sort(const std::string& str) {
	_checkInputAndFillContainer(str);

	std::cout << "Before : ";
	printContainer(_vector);
	double vectorTime = _sortVector();
	double dequeTime = _sortDeque();
	std::cout << "After : ";
	printContainer(_vector);
	std::cout << "Time to process a range of " << _vector.size()
	<< " element with std::vector : " << vectorTime << " us" << std::endl;
	std::cout << "Time to process a range of " << _vector.size()
	<< " element with std::deque : " << dequeTime << " us" << std::endl;
}