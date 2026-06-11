/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 15:23:33 by dufama            #+#    #+#             */
/*   Updated: 2026/06/05 15:23:33 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <cstddef>
#include <deque>
#include <exception>
#include <vector>
#include <iostream>

class PmergeMe {
	private:
		std::vector<int> _vector;
		std::deque<int> _deque;
		void _checkInputAndFillContainer(const std::string& str);
		double _sortVector();
		double _sortDeque();
		
	public:
		// ===== FCO =====
		PmergeMe();
		PmergeMe(const PmergeMe& copy);
		PmergeMe& operator=(const PmergeMe& assign);
		~PmergeMe();

		// ===== Methods =====
		void sort(const std::string& str);
	

		class NumebrError : public std::exception {
			public:
				const char * what() const throw() {
					return "Not a positive number";
				}
		};

		class BadInput : public std::exception {
			public:
				const char * what() const throw() {
					return "Bad input";
				}
		};

		class Overflow : public std::exception {
			public:
				const char * what() const throw() {
					return "Overflow";
				}
		};
};

std::vector<size_t> jacobSthal(size_t maxIndex);

template <typename T>
void printContainer(const T& container) {
	typedef typename T::const_iterator iterator;
	for (iterator it = container.begin(); it != container.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

template <typename T>
size_t findInsertPos(T& container, int valueToInsert, size_t maxLevel) {
	size_t low = 0;
	while (low < maxLevel) {
		size_t mid = low + (maxLevel - low) / 2;
		if (valueToInsert < container[mid])
			maxLevel = mid;
		else
			low = mid + 1;
	}
	return low;
}

// ===== Ford-Johnson function =====
template <typename T>
T fordJohnsonSort(T& toSort) {
	if (toSort.size() <= 1)
		return toSort;

	std::vector<std::pair<int, int> > pairs;
	int rest = -1;
	bool hasRest = false;

	for (size_t i = 0; i + 1 < toSort.size(); i += 2) {
		if (toSort[i] > toSort[i + 1])
			pairs.push_back(std::make_pair(toSort[i], toSort[i + 1]));
		else
			pairs.push_back(std::make_pair(toSort[i + 1], toSort[i]));
	}

	if (toSort.size() % 2 != 0) {
		rest = toSort.back();
		hasRest = true;
	}

	T bigs;
	for (size_t i = 0; i < pairs.size(); ++i) {
		bigs.push_back(pairs[i].first);
	}

	T sortedBigs = fordJohnsonSort(bigs);

	std::vector<std::pair<int, int> > sortedPairs;
	for (size_t i = 0; i < sortedBigs.size(); ++i) {
		for (size_t j = 0; j < pairs.size(); ++j) {
			if (pairs[j].first == sortedBigs[i]) {
				sortedPairs.push_back(pairs[j]);
				pairs.erase(pairs.begin() + j);
				break;
			}
		}
	}
	pairs = sortedPairs;

	T main;
	T pend;

	if (!pairs.empty()) {
		main.push_back(pairs[0].second);
		main.push_back(pairs[0].first);

		for (size_t i = 1; i < pairs.size(); ++i) {
			main.push_back(pairs[i].first);
			pend.push_back(pairs[i].second);
		}
	}
	
	std::vector<size_t> jacob = jacobSthal(pend.size());
	size_t lastJacob = 1;

	for (size_t i = 0; i < jacob.size(); ++i) {
		size_t currentJacob = jacob[i];

		size_t maxIndex = (currentJacob > pend.size()) ? pend.size(): currentJacob;

		for (size_t j = maxIndex; j > lastJacob; --j) {
			int value = pend[j - 1];
			size_t pos = findInsertPos(main, value, main.size());
			main.insert(main.begin() + pos, value);
		}
		lastJacob = maxIndex;
	}

	if (hasRest) {
		size_t pos = findInsertPos(main, rest, main.size());
		main.insert(main.begin() + pos, rest);
	}
	return main;
}


#endif