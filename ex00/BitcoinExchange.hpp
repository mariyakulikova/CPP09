/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 17:12:05 by mkulikov          #+#    #+#             */
/*   Updated: 2025/10/19 15:01:21 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange
{
public:
	struct Date
	{
		int y, m, d;
		Date(): y(0), m(0), d(0) {}
		Date(int yy,int mm,int dd): y(yy), m(mm), d(dd) {}

		int toKey() const;
		bool operator<(const Date&) const;

		static bool isValid(const std::string& s, Date& out);

	private:
		static bool _isLeap(int y);
		static bool _fromString(const std::string& s,int& y,int& m,int& d);
	};

	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange& operator=(const BitcoinExchange& other);
	~BitcoinExchange();

	bool load(const std::string& csvPath);
	bool getRate(const Date& d,double& rate) const;

private:
	std::map<int,double> _rates;
};

#endif
