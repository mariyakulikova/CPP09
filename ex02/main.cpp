/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 17:10:45 by mkulikov          #+#    #+#             */
/*   Updated: 2025/12/07 16:41:22 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <cstdlib>

bool isPositiveNumber(const char* str) {
	if (!str || *str == '\0')
		return false;

	for (int i = 0; str[i]; i++) {
		if (!std::isdigit(str[i]))
			return false;
	}

	return true;
}

void print(const std::string &std, std::vector<int> &vec) {
	std::cout << std;
	for (std::vector<int>::size_type i = 0; i < vec.size(); i++) {
		std::cout << vec[i];
		if (i != vec.size() - 1)
			std::cout << " ";
	}
	std::cout << std::endl;
}

int main(int argc, const char * argv[]) {
	if (argc < 2) {
		std::cerr << "Please provide at least two arguments!\n";
		return 1;
	}

	std::vector<int> vec;
	std::deque<int> dq;

	for (int i = 1; i < argc; i++) {
		const char* arg = argv[i];

		if (!isPositiveNumber(arg)) {
			std::cerr << "Error: \"" << arg << "\" is not a positive number\n";
			return 1;
		}

		long value = std::atoi(arg);

		vec.push_back(value);
		dq.push_back(value);
	}

	print("Before: ", vec);
	
	double durationVec = PmergeMe::sort(vec);
	double durationDeq = PmergeMe::sort(dq);
	
	print("After: ", vec);
	
	std::cout << "Time to process a range of "
			<< vec.size()
			<< " elements with std::vector : "
			<< std::fixed << std::setprecision(5)
			<< durationVec << " us"
			<< std::endl;
			
	std::cout << "Time to process a range of "
			  << dq.size()
			  << " elements with std::deque : "
			  << std::fixed << std::setprecision(5)
			  << durationDeq << " us"
			  << std::endl;
	
	return 0;
}
