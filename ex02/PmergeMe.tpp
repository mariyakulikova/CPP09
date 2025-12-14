/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 14:51:39 by mkulikov          #+#    #+#             */
/*   Updated: 2025/12/14 16:07:40 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

template <typename T>
bool PmergeMe::_comp(T a, T b) {
	PmergeMe::counter++;
	return *a < *b;
}

template <typename T>
void PmergeMe::_swap(T it, size_t level)
{
	T start = _next(it, -level + 1);
	T end = _next(start, level);
	while (start != end)
	{
		std::iter_swap(start, _next(start, level));
		start++;
	}
}

template <typename T>
T PmergeMe::_next(T it, int shift)
{
	std::advance(it, shift);
	return it;
}
