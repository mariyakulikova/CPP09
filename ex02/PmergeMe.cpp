/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 17:10:45 by mkulikov          #+#    #+#             */
/*   Updated: 2025/12/07 16:42:29 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

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
	clock_t start = clock();
	_fordJohnsonSort(vec);
	clock_t end = clock();
	return (double)(end - start) / CLOCKS_PER_SEC * 1000000.0;
}

double PmergeMe::sort(std::deque<int> &dq) {
	clock_t start = clock();
	_fordJohnsonSort(dq);
	clock_t end = clock();
	return (double)(end - start) / CLOCKS_PER_SEC * 1000000.0;
}

std::vector<int> PmergeMe::_jacobsthalSequence(int n) {
	std::vector<int> sequence;

	if (n <= 0) {
		return sequence;
	}

	int j0 = 0;
	int j1 = 1;

	while (j1 <= n) {
		if (j1 > 0 && (sequence.empty() || j1 != sequence.back())) {
			sequence.push_back(j1);
		}

		int j2 = j1 + 2 * j0;
		j0 = j1;
		j1 = j2;
	}

	return sequence;
}

void PmergeMe::_fordJohnsonSort(std::vector<int> &vec) {
	std::vector<int>::size_type n = vec.size();
	
	if (n <= 1) {
		return;
	}

	if (n == 2) {
		if (vec[0] > vec[1]) {
			int tmp = vec[0];
			vec[0] = vec[1];
			vec[1] = tmp;
		}
		return;
	}

	std::vector<int> main;
	std::vector<int> pend;

	main.reserve(n / 2 + 1);
	pend.reserve(n / 2 + 1);

	std::vector<int>::size_type pairCount = n / 2;
	std::vector<int>::size_type i;

	for (i = 0; i < pairCount; ++i) {
		int a = vec[2 * i];
		int b = vec[2 * i + 1];

		if (a < b) {
			pend.push_back(a);
			main.push_back(b);
		} else {
			pend.push_back(b);
			main.push_back(a);
		}
	}

	if (n % 2 != 0) {
		pend.push_back(vec[n - 1]);
	}

	_fordJohnsonSort(main);

	std::vector<int> sorted = main;

	if (!pend.empty()) {
		_binaryInsert(sorted, pend[0]);
	}

	if (pend.size() > 1) {
		std::vector<int> jacob = _jacobsthalSequence(static_cast<int>(pend.size() - 1));

		std::vector<bool> used(pend.size(), false);
		std::vector<int> order;

		used[0] = true;

		for (std::vector<int>::size_type j = 0; j < jacob.size(); ++j) {
			int idx = jacob[j];

			if (idx <= 0)
				continue;
			if (static_cast<std::vector<int>::size_type>(idx) >= pend.size())
				continue;

			if (!used[idx]) {
				order.push_back(idx);
				used[idx] = true;
			}
		}

		for (std::vector<int>::size_type k = 1; k < pend.size(); ++k) {
			if (!used[k]) {
				order.push_back(static_cast<int>(k));
			}
		}

		for (std::vector<int>::size_type t = 0; t < order.size(); ++t) {
			int pendIndex = order[t];
			_binaryInsert(sorted, pend[pendIndex]);
		}
	}

	vec = sorted;
}

void PmergeMe::_binaryInsert(std::vector<int> &vec, int value) {
	std::vector<int>::size_type left = 0;
	std::vector<int>::size_type right = vec.size();
	
	if (vec.empty()) {
		vec.push_back(value);
		return;
	}
	
	while (left < right) {
		std::vector<int>::size_type mid = left + (right - left) / 2;
		if (vec[mid] < value) {
			left = mid + 1;
		}
		else {
			right = mid;
		}
	}
	vec.insert(vec.begin() + static_cast<std::vector<int>::difference_type>(left), value);
}

void PmergeMe::_fordJohnsonSort(std::deque<int> &dq) {
	std::deque<int>::size_type n = dq.size();

	if (n <= 1) {
		return;
	}

	if (n == 2) {
		if (dq[0] > dq[1]) {
			int tmp = dq[0];
			dq[0] = dq[1];
			dq[1] = tmp;
		}
		return;
	}

	std::deque<int> main;
	std::deque<int> pend;

	std::deque<int>::size_type pairCount = n / 2;
	std::deque<int>::size_type i;

	for (i = 0; i < pairCount; ++i) {
		int a = dq[2 * i];
		int b = dq[2 * i + 1];

		if (a < b) {
			pend.push_back(a);
			main.push_back(b);
		} else {
			pend.push_back(b);
			main.push_back(a);
		}
	}

	if (n % 2 != 0) {
		pend.push_back(dq[n - 1]);
	}

	_fordJohnsonSort(main);

	std::deque<int> sorted = main;

	if (!pend.empty()) {
		_binaryInsert(sorted, pend[0]);
	}

	if (pend.size() > 1) {
		std::vector<int> jacob = _jacobsthalSequence(static_cast<int>(pend.size() - 1));

		std::vector<bool> used(pend.size(), false);
		std::deque<int> order;

		used[0] = true;

		for (std::vector<int>::size_type j = 0; j < jacob.size(); ++j) {
			int idx = jacob[j];

			if (idx <= 0)
				continue;
			if (static_cast<std::deque<int>::size_type>(idx) >= pend.size())
				continue;

			if (!used[idx]) {
				order.push_back(idx);
				used[idx] = true;
			}
		}

		for (std::deque<int>::size_type k = 1; k < pend.size(); ++k) {
			if (!used[k]) {
				order.push_back(static_cast<int>(k));
			}
		}

		for (std::deque<int>::size_type t = 0; t < order.size(); ++t) {
			int pendIndex = order[t];
			_binaryInsert(sorted, pend[pendIndex]);
		}
	}

	dq = sorted;
}


void PmergeMe::_binaryInsert(std::deque<int> &dq, int value) {
	if (dq.empty()) {
		dq.push_back(value);
		return;
	}

	std::deque<int>::iterator low = dq.begin();
	std::deque<int>::iterator high = dq.end();

	while (low < high) {
		std::deque<int>::iterator mid = low + (high - low) / 2;

		if (*mid < value) {
			low = mid + 1;
		} else {
			high = mid;
		}
	}

	dq.insert(low, value);
}