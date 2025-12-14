/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 17:10:45 by mkulikov          #+#    #+#             */
/*   Updated: 2025/12/14 18:27:27 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <cstdlib>

int F(int n)
{
	int sum = 0;

	for (int k = 1; k <= n; ++k) {
		double value = (3.0 / 4.0) * k;
		sum += static_cast<int>(ceil(log2(value)));
	}

	return sum;
}

bool isPositiveNumber(const char* str) {
	if (!str || *str == '\0')
		return false;

	for (int i = 0; str[i]; i++) {
		if (!std::isdigit(str[i]))
			return false;
	}

	return true;
}

template<typename Container>
void print(const std::string &str, Container &container) {
	std::cout << str;
	for (typename Container::iterator it = container.begin(); it != container.end(); ++it) {
		std::cout << *it;
		typename Container::iterator nextIt = it;
		++nextIt;
		if (nextIt != container.end())
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
	std::list<int> list;

	for (int i = 1; i < argc; i++) {
		const char* arg = argv[i];

		if (!isPositiveNumber(arg)) {
			std::cerr << "Error: \"" << arg << "\" is not a positive number\n";
			return 1;
		}

		long value = std::atoi(arg);

		vec.push_back(value);
		list.push_back(value);
	}

	print("Before (vector): ", vec);

	double durationVec = PmergeMe::sort(vec);
	double durationList = PmergeMe::sort(list);

	print("After (vector): ", vec);

	std::cout << "Time to process a range of "
			<< vec.size()
			<< " elements with std::vector : "
			<< std::fixed << std::setprecision(5)
			<< durationVec << " us"
			<< std::endl;

	std:: cout << "expected comparisons -> " << F(vec.size()) << std::endl;
	std::cout << "actual comparisons - " << PmergeMe::counter << std::endl;

	std::cout << "Time to process a range of "
			  << list.size()
			  << " elements with std::list : "
			  << std::fixed << std::setprecision(5)
			  << durationList << " us"
			  << std::endl;

	std:: cout << "expected comparisons -> -> " << F(vec.size()) << std::endl;
	std::cout << "actual comparisons - " << PmergeMe::counter << std::endl;

	return 0;
}
