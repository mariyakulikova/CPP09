/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manya <manya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 17:10:45 by mkulikov          #+#    #+#             */
/*   Updated: 2025/11/23 18:07:40 by manya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <vector>
#include <deque>
#include <string>
#include <iostream>

#ifndef _PMERGEME_HPP_
#define _PMERGEME_HPP_

class PmergeMe {
public:
    static void sort(std::vector<int> &vec);
    static void sort(std::deque<int> &dq);

private:
    PmergeMe();
    PmergeMe(const PmergeMe &);
    PmergeMe &operator=(const PmergeMe &);
    ~PmergeMe();

    long _getTime();
    
    template<typename T>
    static void _printSequence(const std::string& prefix, const T& sequence);

    std::vector<int> _vector;
    std::deque<int> _deque;
};

#include "PmergeMe.tpp"

#endif