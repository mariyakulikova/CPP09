/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:09:41 by mkulikov          #+#    #+#             */
/*   Updated: 2025/11/02 16:02:38 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <stdexcept>
#include <sstream>

RPN::RPN() {}
RPN::RPN(const RPN&) {}
RPN& RPN::operator=(const RPN&) { return *this; }
RPN::~RPN() {}

bool RPN::isDigitToken(const std::string& tok) {
	return tok.size() == 1 && tok[0] >= '0' && tok[0] <= '9';
}

bool RPN::isOperator(const std::string& tok) {
	return tok.size() == 1 && (tok[0] == '+' || tok[0] == '-' || tok[0] == '*' || tok[0] == '/');
}

long RPN::compute(long a, long b, char op) {
	switch (op) {
		case '+': return a + b;
		case '-': return a - b;
		case '*': return a * b;
		case '/':
			if (b == 0) throw std::runtime_error("division by zero");
			return a / b;
	}
	throw std::runtime_error("unknown operator");
}

long RPN::evaluate(const std::string& expr) {
	if (expr.empty()) throw std::runtime_error("empty");

	std::stack<long> st;

	std::string tok;
	std::istringstream iss(expr);
	while (iss >> tok) {
		if (isDigitToken(tok)) {
			st.push(static_cast<long>(tok[0] - '0'));
		} else if (isOperator(tok)) {
			if (st.size() < 2) throw std::runtime_error("not enough operands");
			long b = st.top();
			st.pop();
			long a = st.top();
			st.pop();
			long result = compute(a, b, tok[0]);
			st.push(result);
		} else {
			throw std::runtime_error("bad token");
		}
	}

	if (st.size() != 1) throw std::runtime_error("leftover operands");
	return st.top();
}
