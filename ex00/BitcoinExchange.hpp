#pragma once

#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>

class Date {

private:
		int year;
		int month;
		int day;
		Date();
	public:
		Date(std::string date_string);
		Date(const Date& copy);
		~Date();

		int getYear() const;
		int getMonth() const;
		int getDay() const;
};

bool operator<(const Date& lhs, const Date& rhs);
struct DateComparator{bool operator()(const Date &lhs, const Date &rhs) const;};

std::ostream& operator<<(std::ostream& output, const Date& source);

class BitcoinExchange {
	private:
		std::map<Date, double> data;
		std::ifstream input_file;
		BitcoinExchange(void);
		BitcoinExchange(BitcoinExchange& copy);
		BitcoinExchange& operator=(BitcoinExchange& copy);
	public:
		BitcoinExchange(std::string file);
		~BitcoinExchange(void);

		void	convert(void);
};