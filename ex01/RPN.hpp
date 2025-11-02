/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:09:44 by mkulikov          #+#    #+#             */
/*   Updated: 2025/11/02 16:01:25 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <stack>

class RPN {
public:
	static long evaluate(const std::string& expr);

private:
	RPN();
	RPN(const RPN&);
	RPN& operator=(const RPN&);
	~RPN();

	static bool isDigitToken(const std::string& tok);
	static bool isOperator(const std::string& tok);
	static long compute(long a, long b, char op);
};

#endif
