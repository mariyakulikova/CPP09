/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 17:10:45 by mkulikov          #+#    #+#             */
/*   Updated: 2025/12/07 16:41:45 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <vector>
#include <deque>
#include <string>
#include <iostream>
#include <iomanip>

#ifndef _PMERGEME_HPP_
#define _PMERGEME_HPP_

class PmergeMe {
public:
	static double sort(std::vector<int> &vec);
	static double sort(std::deque<int> &dq);

private:
	PmergeMe();
	PmergeMe(const PmergeMe &);
	PmergeMe &operator=(const PmergeMe &);
	~PmergeMe();
	
	static std::vector<int> _jacobsthalSequence(int n);
	static void _fordJohnsonSort(std::vector<int> &vec);
	static void _binaryInsert(std::vector<int> &vec, int value);
	static void _fordJohnsonSort(std::deque<int> &dq);
	static void _binaryInsert(std::deque<int> &dq, int value);
};

#endif