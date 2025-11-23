/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manya <manya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 17:10:45 by mkulikov          #+#    #+#             */
/*   Updated: 2025/11/23 18:07:32 by manya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe() {}

PmergeMe& PmergeMe::operator=(const PmergeMe &other) {
    if (this != &other) {
        _vector = other._vector;
        _deque = other._deque;
    }
    return *this;
}

PmergeMe::PmergeMe(const PmergeMe &other): _vector(other._vector), _deque(other._deque) {}

long PmergeMe::_getTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000) + tv.tv_usec;
}

void PmergeMe::sort(std::vector<int> &vec) {
    std::cout << "Sorting vector..." << std::endl;
    _printSequence("Before: ", vec);
}

void PmergeMe::sort(std::deque<int> &dq) {
    std::cout << "Sorting deque..." <<  std::endl;
    _printSequence("Before: ", dq);
}