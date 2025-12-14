/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 17:10:45 by mkulikov          #+#    #+#             */
/*   Updated: 2025/12/14 18:28:59 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>

#ifndef _PMERGEME_HPP_
#define _PMERGEME_HPP_

class PmergeMe {
public:
	static double sort(std::vector<int> &vec);
	static double sort(std::list<int> &dq);
	static int counter;

private:
	PmergeMe();
	PmergeMe(const PmergeMe &);
	PmergeMe &operator=(const PmergeMe &);
	~PmergeMe();

	static int _jacobstahlNumber(size_t n);
	static void _fordJohnsonSort(std::vector<int> &vec, size_t level);
	static void _fordJohnsonSort(std::list<int> &list, size_t level);
	template<typename T> static bool _comp(T a, T b);
	template <typename T> static void _swap(T it, size_t level);
	template <typename T> static T _next(T it, int shift);
};

#include "PmergeMe.tpp"

#endif
