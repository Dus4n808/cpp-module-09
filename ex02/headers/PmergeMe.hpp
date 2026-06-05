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

#include <deque>
#include <exception>
#include <vector>

class PmergeMe {
	private:
		std::vector<int> _vector;
		std::deque<int> _deque;
		void fill(const std::string& str);
	public:
		// ===== FCO =====
		PmergeMe();
		PmergeMe(const PmergeMe& copy);
		PmergeMe& operator=(const PmergeMe& assign);
		~PmergeMe();

		// ===== Methods =====
		void test(std::string& str);

		class NumebrError : public std::exception {
			public:
				const char * what() const throw() {
					return "Not a positive number";
				}
		};

		class BadInput : public std::exception {
			public:
				const char * what() const throw() {
					return "Not a number";
				}
		};

		class Overflow : public std::exception {
			public:
				const char * what() const throw() {
					return "Overflow";
				}
		};
};

#endif