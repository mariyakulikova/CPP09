/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 17:10:45 by mkulikov          #+#    #+#             */
/*   Updated: 2025/10/19 18:14:40 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <cstdlib>

bool BitcoinExchange::Date::_isLeap(int y)
{
	return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

bool BitcoinExchange::Date::_fromString(const std::string& s,
										int& y,int& m,int& d)
{
	std::istringstream ss(s);
	char a,b;
	return (ss >> y >> a >> m >> b >> d) && a=='-' && b=='-';
}

bool BitcoinExchange::Date::isValid(const std::string& s, Date& out)
{
	if (s.size()!=10 || s[4]!='-' || s[7]!='-')
	{
		return false;
	}

	int y,m,d;
	if (!_fromString(s,y,m,d)){
		return false;
	}

	if (y<0 || m<1 || m>12 || d<1)
	{
		return false;
	}

	static const int md[12]={31,28,31,30,31,30,31,31,30,31,30,31};
	int maxd = md[m-1] + (m==2 && _isLeap(y) ? 1 : 0);
	if (d>maxd)
	{
		return false;
	}

	out = Date(y,m,d);
	return true;
}

int BitcoinExchange::Date::toKey() const
{
	return y*10000 + m*100 + d;
}

bool BitcoinExchange::Date::operator<(const Date& r) const
{
	return toKey() < r.toKey();
}

std::string BitcoinExchange::Utils::_ltrim(const std::string& s)
{
	size_t p = s.find_first_not_of(" \t");
	return p == std::string::npos ? "" : s.substr(p);
}

std::string BitcoinExchange::Utils::_rtrim(const std::string& s)
{
	size_t p = s.find_last_not_of(" \t");
	return p == std::string::npos ? "" : s.substr(0, p + 1);
}

std::string BitcoinExchange::Utils::trim(const std::string& s)
{
	return _rtrim(_ltrim(s));
}

bool BitcoinExchange::Utils::isNumber(const std::string& s)
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

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
	: _rates(other._rates) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
	{
		_rates = other._rates;
	}
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::exchange(const std::string &line)
{
	if (line.empty())
	{
		std::cout << "Error: bad input => " << line << "\n";
		return;
	}

	if (Utils::trim(line) == FORMAT)
	{
		return;
	}

	size_t bar = line.find('|');
	if (bar == std::string::npos)
	{
		std::cout << "Error: bad input => " << line << "\n";
		return;
	}

	std::string dateStr = Utils::trim(line.substr(0, bar));
	std::string valStr  = Utils::trim(line.substr(bar + 1));

	Date date;
	if (!Date::isValid(dateStr, date))
	{
		std::cout << "Error: bad input => " << dateStr << "\n";
		return;
	}

	if (!Utils::isNumber(valStr))
	{
		std::cout << "Error: bad input => " << valStr << "\n";
		return;
	}

	double value = std::strtod(valStr.c_str(), 0);
	if (value <= 0)
	{
		std::cout << "Error: not a positive number.\n";
		return;
	}
	if (value > 1000)
	{
		std::cout << "Error: too large a number.\n";
		return;
	}

	double rate;
	if (!getRate(date, rate))
	{
		std::cout << "Error: bad input => " << line << "\n";
		return;
	}

	std::cout << dateStr << " => " << valStr << " = " << value * rate << "\n";
}

bool BitcoinExchange::load(const std::string& path)
{
	std::ifstream f(path.c_str());
	if (!f)
	{
		return false;
	}

	std::string line; std::getline(f,line);
	while (std::getline(f,line))
	{
		if (line.empty())
		{
			continue;
		}

		std::istringstream ss(line);
		std::string dateStr, priceStr;
		if (!std::getline(ss,dateStr,',') || !std::getline(ss,priceStr))
		{
			continue;
		}

		Date d;
		if (!Date::isValid(dateStr,d))
		{
			continue;
		}

		_rates[d.toKey()] = std::atof(priceStr.c_str());
	}
	return !_rates.empty();
}

bool BitcoinExchange::getRate(const Date& d,double& rate) const
{
	if (_rates.empty())
	{
		return false;
	}

	int key = d.toKey();
	std::map<int,double>::const_iterator it = _rates.lower_bound(key);

	if (it!=_rates.end() && it->first==key)
	{
		rate = it->second;
		return true;
	}

	if (it==_rates.begin())
	{
		return false;
	}

	--it;
	rate = it->second;
	return true;
}
