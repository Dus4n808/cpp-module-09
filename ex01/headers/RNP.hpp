/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RNP.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 10:24:25 by dufama            #+#    #+#             */
/*   Updated: 2026/06/05 10:24:25 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <exception>
#include <stack>

class RPN {
	private:
		std::stack<int> _stack;
		// ===== FCO =====
		RPN(const RPN& copy);
		RPN& operator=(const RPN& assign);
		void makeCalcul(char c);

	public:
		// ===== FCO =====
		RPN();
		~RPN();
		int solve(const std::string& str);

		class InvalidInput : public std::exception {
			public:
				const char * what() const throw() {
					return "Invalid input";
				}
		};

		class ErrorDivision : public std::exception {
			public:
				const char * what() const throw() {
					return "Division by zero";
				}
		};
		
};

#endif