/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 10:34:13 by dufama            #+#    #+#             */
/*   Updated: 2026/06/05 10:34:13 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/RNP.hpp"
#include <sstream>

// ================================================================ //
// FCO                       
// ================================================================ //

// ===== Default Constructor =====
RPN::RPN() : _stack() {}

// ===== Destructor =====
RPN::~RPN() {}

// ================================================================ //
// Methods                       
// ================================================================ //

static bool isOperator(char c) {
	return c == '+' || c == '-' || c == '*' || c == '/';
}


void RPN::makeCalcul(char c) {
	if (_stack.size() < 2)
		throw InvalidInput();
	int a = _stack.top();
	_stack.pop();
	int b = _stack.top();
	_stack.pop();
	int res = 0;
	switch (c) {
		case '+':
			res = a + b;
			break;
		case '/':
			if (a == 0)
				throw ErrorDivision();
			res = b / a;
			break;
		case '-':
			res = b - a;
			break;
		case '*':
			res = a * b;
			break;
	}
	_stack.push(res);
}

int RPN::solve(const std::string& str) {
	std::istringstream ss(str);
	std::string token;

	while (ss >> token) {
		if (token.size() == 1 && token[0] >= '0' && token[0] <= '9') {
			int value = token[0] - '0';
			_stack.push(value);
		}
		else if (token.size() == 1 && isOperator(token[0])){
			makeCalcul(token[0]);
		}
		else {
			throw InvalidInput();
		}
	}
	if (_stack.size() != 1)
		throw InvalidInput();
	return _stack.top();
}
