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
#include <exception>
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

void PmergeMe::_fill(const std::string& str) {

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


// static void printDeque(const std::deque<int>& d) {
// 	std::deque<int>::const_iterator it;
// 	for (it = d.begin(); it != d.end(); ++it) {
// 		std::cout << "Deque : " << *it << std::endl;
// 	}
// }

static void printVector(const std::vector<int>& v) {
	std::vector<int>::const_iterator it;
	for (it = v.begin(); it != v.end(); ++it) {
		std::cout << "["<< *it << "]";
	}
	std::cout << std::endl;
}

// static void printPairs(const std::vector<std::pair<int, int> >& vec) {
// 	std::vector<std::pair<int, int> >::const_iterator it;
// 	for (it = vec.begin(); it != vec.end(); ++it) {
// 		std::cout << "Big : " << it->first << " Small : " << it->second << std::endl;
// 	}
// }
// 

// ===== Search dichotomic =====
// static size_t dichotomieSearch(std::vector<int>& vToInsert, int valueToInsert, size_t maxLevel) {
// 	size_t low = 0;
// 	while (low < maxLevel) {
// 		size_t mid = low + (maxLevel - low) / 2;
// 		if (valueToInsert < vToInsert[mid])
// 			maxLevel = mid;
// 		else
// 			low = mid + 1;
// 	}
// 	return low;
// }

// ===== Generator JacobSthal =====

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

// // ===== Ford-Johnson vector =====
// static std::vector<int> fjSortVector(std::vector<int>& toSort) {
// 	if (toSort.size() <= 1)
// 		return toSort;

// 	std::vector<std::pair<int, int> > pairs;
// 	int rest = -1;
// 	bool hasRest = false;

// 	for (size_t i = 0; i + 1 < toSort.size(); i += 2) {
// 		if (toSort[i] > toSort[i + 1])
// 			pairs.push_back(std::make_pair(toSort[i], toSort[i + 1]));
// 		else
// 			pairs.push_back(std::make_pair(toSort[i + 1], toSort[i]));
// 	}

// 	if (toSort.size() % 2 != 0) {
// 		rest = toSort.back();
// 		hasRest = true;
// 	}

// 	std::vector<int> bigs;
// 	for (size_t i = 0; i < pairs.size(); ++i) {
// 		bigs.push_back(pairs[i].first);
// 	}

// 	std::vector<int> sortedBigs = fjSortVector(bigs);

// 	std::vector<std::pair<int, int> > sortedPairs;
// 	for (size_t i = 0; i < sortedBigs.size(); ++i) {
// 		for (size_t j = 0; j < pairs.size(); ++j) {
// 			if (pairs[j].first == sortedBigs[i]) {
// 				sortedPairs.push_back(pairs[j]);
// 				pairs.erase(pairs.begin() + j);
// 				break;
// 			}
// 		}
// 	}
// 	pairs = sortedPairs;

// 	std::vector<int> main;
// 	std::vector<int> pend;

// 	if (!pairs.empty()) {
// 		main.push_back(pairs[0].second);
// 		main.push_back(pairs[0].first);

// 		for (size_t i = 1; i < pairs.size(); ++i) {
// 			main.push_back(pairs[i].first);
// 			pend.push_back(pairs[i].second);
// 		}
// 	}

// 	std::vector<size_t> jacob = jacobSthal(pend.size());
// 	size_t lastJacob = 1;

// 	for (size_t i = 0; i < jacob.size(); ++i) {
// 		size_t currentJacob = jacob[i];

// 		size_t maxIndex = (currentJacob > pend.size()) ? pend.size(): currentJacob;

// 		for (size_t j = maxIndex; j > lastJacob; --j) {
// 			int value = pend[j - 1];
// 			size_t pos = dichotomieSearch(main, value, main.size());
// 			main.insert(main.begin() + pos, value);
// 		}
// 		lastJacob = maxIndex;
// 	}

// 	if (hasRest) {
// 		size_t pos = dichotomieSearch(main, rest, main.size());
// 		main.insert(main.begin() + pos, rest);
// 	}
// 	return main;
// }

void PmergeMe::sortVector(std::string& str) {
	std::vector<int> sort;
	try {
		_fill(str);
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	printVector(_vector);
	_vector = fjSortVector(_vector);
	printVector(_vector);
}