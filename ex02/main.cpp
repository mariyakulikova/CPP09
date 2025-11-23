/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manya <manya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 17:10:45 by mkulikov          #+#    #+#             */
/*   Updated: 2025/11/23 17:53:10 by manya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <cstdlib>
#include <cctype>

bool isPositiveNumber(const char* str) {
    if (!str || *str == '\0')
        return false;

    for (int i = 0; str[i]; i++) {
        if (!std::isdigit(str[i]))
            return false;
    }

    return true;
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

        if (value <= 0) {
            std::cerr << "Error: number must be > 0: " << arg << "\n";
            return 1;
        }

        vec.push_back(value);
        dq.push_back(value);
    }

    PmergeMe::sort(vec);
    PmergeMe::sort(dq);
    
    return 0;
}
