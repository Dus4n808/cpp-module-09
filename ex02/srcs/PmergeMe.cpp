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
#include <deque>
#include <limits>
#include <sstream>
#include <iostream>
#include <string>
#include <utility>
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


static void printDeque(const std::deque<int>& d) {
	std::deque<int>::const_iterator it;
	for (it = d.begin(); it != d.end(); ++it) {
		std::cout << "Deque : " << *it << std::endl;
	}
}

static void printVector(const std::vector<int>& v) {
	std::vector<int>::const_iterator it;
	int index = 0;
	for (it = v.begin(); it != v.end(); ++it) {
		std::cout << "Vector : index " << index << " : " << *it << std::endl;
		index++;
	}
}

static void printPairs(const std::vector<std::pair<int, int> >& vec) {
	std::vector<std::pair<int, int> >::const_iterator it;
	for (it = vec.begin(); it != vec.end(); ++it) {
		std::cout << "Big : " << it->first << " Small : " << it->second << std::endl;
	}
}


// ===== Make pairs vector =====
std::vector<std::pair<int, int> > splitPair(std::vector<int>& toSplit) {
	std::vector<std::pair<int, int> > pairs;
	
	for (size_t i = 0; i + 1 < toSplit.size(); i += 2) {
		if (toSplit[i] > toSplit[i + 1])
			pairs.push_back(std::make_pair(toSplit[i], toSplit[i + 1]));
		else
			pairs.push_back(std::make_pair(toSplit[i + 1], toSplit[i]));
	}
	return pairs;
}

// ===== Make pairs vector with last value stock =====
std::vector<std::pair<int, int> > splitUnPair(std::vector<int>& toSplit, int *lastValue) {
	std::vector<std::pair<int, int> > pairs;

	*lastValue = toSplit.back();
	for (size_t i = 0; i + 1 < toSplit.size(); i += 2) {
		if (toSplit[i] > toSplit[i + 1])
			pairs.push_back(std::make_pair(toSplit[i], toSplit[i + 1]));
		else
			pairs.push_back(std::make_pair(toSplit[i + 1], toSplit[i]));
	}
	return pairs;
} 

void PmergeMe::sort(std::string& str) {
	fill(str);
	(void)printDeque;
	(void)printVector;
	int value = - 1;
	if (_vector.size() % 2 == 0)
		printPairs(splitPair(_vector));
	else
		printPairs(splitUnPair(_vector, &value));
	std::cout << value << std::endl;
}