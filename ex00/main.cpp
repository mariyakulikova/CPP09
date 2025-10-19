/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 18:17:16 by mkulikov          #+#    #+#             */
/*   Updated: 2025/10/19 16:08:57 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <string>

static std::string ltrim(const std::string& s)
{
	size_t p = s.find_first_not_of(" \t");
	return p == std::string::npos ? "" : s.substr(p);
}

static std::string rtrim(const std::string& s)
{
	size_t p = s.find_last_not_of(" \t");
	return p == std::string::npos ? "" : s.substr(0, p + 1);
}

static std::string trim(const std::string& s)
{
	return rtrim(ltrim(s));
}

static bool isNumber(const std::string& s)
{
	if (s.empty())
	{
		return false;
	}

	size_t i = 0;
	if (s[i] == '-')
	{
		++i;
	}
	bool dot = false;
	bool digit = false;
	for (; i < s.size(); ++i)
	{
		char c = s[i];
		if (c == '.')
		{
			if (dot) return false;
			dot = true;
		}
		else if (std::isdigit(static_cast<unsigned char>(c)))
		{
			digit = true;
		}
		else
		{
			return false;
		}
	}
	return digit;
}

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << "Error: could not open file.\n";
		return 1;
	}

	BitcoinExchange bex;
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

	std::string line;

	if (!std::getline(in, line))
	{
		return 0;
	}

	std::getline(in, line);
	while (std::getline(in, line))
	{
		if (line.empty())
		{
			std::cout << "Error: bad input => " << line << "\n";
			continue;
		}

		size_t bar = line.find('|');
		if (bar == std::string::npos)
		{
			std::cout << "Error: bad input => " << line << "\n";
			continue;
		}

		std::string dateStr = trim(line.substr(0, bar));
		std::string valStr  = trim(line.substr(bar + 1));

		BitcoinExchange::Date date;
		if (!BitcoinExchange::Date::isValid(dateStr, date))
		{
			std::cout << "Error: bad input => " << dateStr << "\n";
			continue;
		}

		if (!isNumber(valStr))
		{
			std::cout << "Error: bad input => " << line << "\n";
			continue;
		}

		double value = std::strtod(valStr.c_str(), 0);
		if (value <= 0)
		{
			std::cout << "Error: not a positive number.\n";
			continue;
		}
		if (value > 1000)
		{
			std::cout << "Error: too large a number.\n";
			continue;
		}

		double rate;
		if (!bex.getRate(date, rate))
		{
			std::cout << "Error: bad input => " << line << "\n";
			continue;
		}

		std::cout << dateStr << " => " << valStr << " = " << value * rate << "\n";
	}
	return 0;
}
