/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 17:10:45 by mkulikov          #+#    #+#             */
/*   Updated: 2025/12/14 18:11:57 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int PmergeMe::counter = 0;

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe() {}

PmergeMe& PmergeMe::operator=(const PmergeMe &other) {
	(void)other;
	return *this;
}

PmergeMe::PmergeMe(const PmergeMe &other) {
	(void)other;
}

double PmergeMe::sort(std::vector<int> &vec) {
	counter = 0;
	clock_t start = clock();
	_fordJohnsonSort(vec, 1);
	clock_t end = clock();
	return (double)(end - start) / CLOCKS_PER_SEC * 1000000.0;
}

double PmergeMe::sort(std::list<int> &list) {
	counter = 0;
	clock_t start = clock();
	_fordJohnsonSort(list, 1);
	clock_t end = clock();
	return (double)(end - start) / CLOCKS_PER_SEC * 1000000.0;
}

int PmergeMe::_jacobstahlNumber(size_t n) {
	return round((pow(2, n + 1) + pow(-1, n)) / 3);
}

void PmergeMe::_fordJohnsonSort(std::vector<int> &vec, size_t level) {
	int _level = static_cast<int>(level);

	int pairsNbr = vec.size() / _level;
	if (pairsNbr < 2)
		return;

	bool isOdd = pairsNbr % 2 == 1;

	std::vector<int>::iterator start = vec.begin();
	std::vector<int>::iterator last = _next(vec.begin(), _level * (pairsNbr));
	std::vector<int>::iterator end = _next(last, -(isOdd * _level));

	int jump = 2 * _level;
	for (std::vector<int>::iterator it = start; it != end; std::advance(it, jump)) {
		std::vector<int>::iterator currPair = _next(it, _level - 1);
		std::vector<int>::iterator _nextPair = _next(it, _level * 2 - 1);
		if (_comp(_nextPair, currPair))
			_swap(currPair, _level);
	}
	_fordJohnsonSort(vec, _level * 2);

	std::vector<std::vector<int>::iterator> main;
	std::vector<std::vector<int>::iterator> pend;

	main.push_back(_next(vec.begin(), _level - 1));
	main.push_back(_next(vec.begin(), _level * 2 - 1));

	for (int i = 4; i <= pairsNbr; i += 2) {
		pend.push_back(_next(vec.begin(), _level * (i - 1) - 1));
		main.push_back(_next(vec.begin(), _level * i - 1));
	}

	if (isOdd)
		pend.push_back(_next(end, _level - 1));

	int prevJacobstahl = _jacobstahlNumber(1);
	int insertedCounter = 0;
	for (int k = 2;; k++)
	{
		int currJacobstahl = _jacobstahlNumber(k);
		int jacobsthalDiff = currJacobstahl - prevJacobstahl;
		int offset = 0;
		if (jacobsthalDiff > static_cast<int>(pend.size()))
			break;
		int toInsert = jacobsthalDiff;
		std::vector<std::vector<int>::iterator>::iterator pendIt = _next(pend.begin(), jacobsthalDiff - 1);
		std::vector<std::vector<int>::iterator>::iterator boundIt = _next(main.begin(), currJacobstahl + insertedCounter);
		while (toInsert)
		{
			std::vector<std::vector<int>::iterator>::iterator idx = std::upper_bound(main.begin(), boundIt, *pendIt, _comp<std::vector<int>::iterator>);
			std::vector<std::vector<int>::iterator>::iterator inserted = main.insert(idx, *pendIt);
			toInsert--;
			pendIt = pend.erase(pendIt);
			std::advance(pendIt, -1);
			offset += (inserted - main.begin()) == currJacobstahl + insertedCounter;
			boundIt = _next(main.begin(), currJacobstahl + insertedCounter - offset);
		}
		prevJacobstahl = currJacobstahl;
		insertedCounter += jacobsthalDiff;
		offset = 0;
	}

	for (ssize_t i = pend.size() - 1; i >= 0; i--)
	{
		std::vector<std::vector<int>::iterator>::iterator curr_pend = _next(pend.begin(), i);
		std::vector<std::vector<int>::iterator>::iterator curr_bound = _next(main.begin(), main.size() - pend.size() + i + isOdd);
		std::vector<std::vector<int>::iterator>::iterator idx = std::upper_bound(main.begin(), curr_bound, *curr_pend, _comp<std::vector<int>::iterator>);
		main.insert(idx, *curr_pend);
	}

	std::vector<int> copy;
	copy.reserve(vec.size());
	for (std::vector<std::vector<int>::iterator>::iterator it = main.begin(); it != main.end(); it++)
	{
		for (int i = 0; i < _level; i++)
		{
			std::vector<int>::iterator pair_start = *it;
			std::advance(pair_start, -_level + i + 1);
			copy.insert(copy.end(), *pair_start);
		}
	}

	std::vector<int>::iterator vecIt = vec.begin();
	std::vector<int>::iterator copyIt = copy.begin();
	while (copyIt != copy.end()) {
		*vecIt++ = *copyIt++;
	}
}

void PmergeMe::_fordJohnsonSort(std::list<int> &list, size_t level) {
	int _level = static_cast<int>(level);

	int pairsNbr = list.size() / _level;
	if (pairsNbr < 2)
		return;

	bool isOdd = pairsNbr % 2 == 1;

	std::list<int>::iterator start = list.begin();
	std::list<int>::iterator last = _next(list.begin(), _level * (pairsNbr));
	std::list<int>::iterator end = _next(last, -(isOdd * _level));

	int jump = 2 * _level;
	for (std::list<int>::iterator it = start; it != end; std::advance(it, jump)) {
		std::list<int>::iterator currPair = _next(it, _level - 1);
		std::list<int>::iterator _nextPair = _next(it, _level * 2 - 1);
		if (_comp(_nextPair, currPair))
			_swap(currPair, _level);
	}
	_fordJohnsonSort(list, _level * 2);

	std::list<std::list<int>::iterator> main;
	std::list<std::list<int>::iterator> pend;

	main.push_back(_next(list.begin(), _level - 1));
	main.push_back(_next(list.begin(), _level * 2 - 1));

	for (int i = 4; i <= pairsNbr; i += 2) {
		pend.push_back(_next(list.begin(), _level * (i - 1) - 1));
		main.push_back(_next(list.begin(), _level * i - 1));
	}

	if (isOdd)
		pend.push_back(_next(end, _level - 1));

	int prevJacobstahl = _jacobstahlNumber(1);
	int insertedCounter = 0;
	for (int k = 2;; k++) {
		int currJacobstahl = _jacobstahlNumber(k);
		int jacobsthalDiff = currJacobstahl - prevJacobstahl;
		int offset = 0;
		if (jacobsthalDiff > static_cast<int>(pend.size()))
			break;
		int toInsert = jacobsthalDiff;
		std::list<std::list<int>::iterator>::iterator pendIt = _next(pend.begin(), jacobsthalDiff - 1);
		std::list<std::list<int>::iterator>::iterator boundIt = _next(main.begin(), currJacobstahl + insertedCounter);
		while (toInsert) {
			std::list<std::list<int>::iterator>::iterator idx = std::upper_bound(main.begin(), boundIt, *pendIt, _comp<std::list<int>::iterator>);
			std::list<std::list<int>::iterator>::iterator inserted = main.insert(idx, *pendIt);
			toInsert--;
			pendIt = pend.erase(pendIt);
			std::advance(pendIt, -1);
			offset += std::distance(main.begin(), inserted) == currJacobstahl + insertedCounter;
			boundIt = _next(main.begin(), currJacobstahl + insertedCounter - offset);
		}
		prevJacobstahl = currJacobstahl;
		insertedCounter += jacobsthalDiff;
		offset = 0;
	}

	for (ssize_t i = pend.size() - 1; i >= 0; i--) {
		std::list<std::list<int>::iterator>::iterator curr_pend = _next(pend.begin(), i);
		std::list<std::list<int>::iterator>::iterator curr_bound = _next(main.begin(), main.size() - pend.size() + i + isOdd);
		std::list<std::list<int>::iterator>::iterator idx = std::upper_bound(main.begin(), curr_bound, *curr_pend, _comp<std::list<int>::iterator>);
		main.insert(idx, *curr_pend);
	}

	std::list<int> copy;
	for (std::list<std::list<int>::iterator>::iterator it = main.begin(); it != main.end(); it++) {
		for (int i = 0; i < _level; i++) {
			std::list<int>::iterator pair_start = *it;
			std::advance(pair_start, -_level + i + 1);
			copy.push_back(*pair_start);
		}
	}

	std::list<int>::iterator listIt = list.begin();
	std::list<int>::iterator copyIt = copy.begin();
	while (copyIt != copy.end()) {
		*listIt++ = *copyIt++;
	}
}
