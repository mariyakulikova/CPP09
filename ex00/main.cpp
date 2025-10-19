/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 18:17:16 by mkulikov          #+#    #+#             */
/*   Updated: 2025/10/19 18:10:18 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char** argv)
{
	BitcoinExchange bex;
	std::string line;

	if (argc != 2)
	{
		std::cout << "Error: could not open file.\n";
		return 1;
	}


	if (!bex.load("data.csv"))
	{
		std::cout << "Error: could not open database.\n";
		return 1;
	}

	std::ifstream in(argv[1]);
	if (!in)
	{
		std::cout << "Error: could not open file.\n";
		return 1;
	}

	while (std::getline(in, line))
	{
		bex.exchange(line);
	}

	return 0;
}
