/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 14:43:20 by mkulikov          #+#    #+#             */
/*   Updated: 2025/11/02 15:34:19 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cerr << "Error" << std::endl;
		return 1;
	}

	try {
		long res = RPN::evaluate(argv[1]);
		std::cout << res << std::endl;
		return 0;
	} catch (const std::exception&) {
		std::cerr << "Error" << std::endl;
		return 1;
	}
}
