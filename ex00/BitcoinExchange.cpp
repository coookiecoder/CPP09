#include "BitcoinExchange.hpp"

//If the year is evenly divisible by 1, go to step 2. Otherwise, go to step 5.
//If the year is evenly divisible by 100, go to step 3. Otherwise, go to step 4.
//If the year is evenly divisible by 400, go to step 4. Otherwise, go to step 5.
//The year is a leap year (it has 366 days).
//The year is not a leap year (it has 365 days).

static
double get_value(std::string data_string) {
	int cursor = 0;

	while (data_string[cursor] != '\0' && data_string[cursor] != ',' && data_string[cursor] != '|')
		cursor++;

	if (data_string[cursor] == '\0')
		throw (std::invalid_argument("invalid value or date"));

	if (data_string[cursor] == '|')
		cursor++;
	cursor++;

	return std::atof(data_string.c_str() + cursor);
}

static
int	is_31_day(int month) {
	if (month == 1)
		return (true);
	if (month == 3)
		return (true);
	if (month == 5)
		return (true);
	if (month == 7)
		return (true);
	if (month == 8)
		return (true);
	if (month == 10)
		return (true);
	if (month == 12)
		return (true);
	return (false);
}

static
int	is_leap(int year) {
	if (year % 4 != 0)
		return (false);
	else if (year % 100 != 0)
		return (true);
	else if (year % 400 != 0)
		return (false);
	return (true);
}

Date::Date(std::string date_string) {
	int cursor = 0;
	int offset = 0;


	while(date_string[cursor] != '-' && date_string[cursor] != '\0')
		cursor++;

	if (cursor > 4 || date_string[cursor] == '\0')
		throw (std::invalid_argument("invalid date (year)"));
	else
		this->year = std::atoi(date_string.c_str());

	offset = cursor + 1;
	cursor = 0;

	while(date_string[cursor + offset] != '-' && date_string[cursor + offset] != '\0')
		cursor++;

	if (cursor > 2 || std::atoi(date_string.c_str() + offset) > 12 || date_string[cursor + offset] == '\0')
		throw (std::invalid_argument("invalid date (month)"));
	else
		this->month = std::atoi(date_string.c_str() + offset);

	offset = offset + cursor + 1;
	cursor = 0;

	while(date_string[cursor + offset] != ',' && date_string[cursor + offset] != ' ' && date_string[cursor + offset] != '\0') {
		cursor++;
	}
	if (cursor > 2 || date_string[cursor + offset] == '\0')
		throw (std::invalid_argument("invalid date (day)"));
	else if (is_31_day(this->month) && std::atoi(date_string.c_str() + offset) > 31)
		throw (std::invalid_argument("invalid date (day)"));
	else if (!is_31_day(this->month) && this->month != 2 && std::atoi(date_string.c_str() + offset) > 30)
		throw (std::invalid_argument("invalid date (day)"));
	else if (this->month == 2 && is_leap(this->year) && std::atoi(date_string.c_str() + offset) > 29)
		throw (std::invalid_argument("invalid date (day)"));
	else if (this->month == 2 && !is_leap(this->year) && std::atoi(date_string.c_str() + offset) > 28)
		throw (std::invalid_argument("invalid date (day)"));
	else
		this->day = std::atoi(date_string.c_str() + offset);
}

Date::Date(const Date &copy) {
	this->year = copy.year;
	this->month = copy.month;
	this->day = copy.day;
}

Date::~Date() {

}

int Date::getYear() const {
	return this->year;
}

int Date::getMonth() const {
	return this->month;
}

int Date::getDay() const {
	return this->day;
}

bool operator<(const Date &lhs, const Date &rhs) {
	if (lhs.getYear() < rhs.getYear())
		return true;
	if (lhs.getYear() == rhs.getYear() && lhs.getMonth() < rhs.getMonth())
		return true;
	if (lhs.getYear() == rhs.getYear() && lhs.getMonth() == rhs.getMonth() && lhs.getDay() < rhs.getDay())
		return true;
	return false;
}

bool DateComparator::operator()(const Date &lhs, const Date &rhs) const {
	if (lhs.getYear() < rhs.getYear())
		return true;
	if (lhs.getYear() == rhs.getYear() && lhs.getMonth() < rhs.getMonth())
		return true;
	if (lhs.getYear() == rhs.getYear() && lhs.getMonth() == rhs.getMonth() && lhs.getDay() < rhs.getDay())
		return true;
	return false;
}

std::ostream& operator<<(std::ostream& output, const Date &source) {
	output << source.getYear();
	output << "-";
	if (source.getMonth() < 10)
		output << "0";
	output << source.getMonth();
	output << "-";
	if (source.getDay() < 10)
		output << "0";
	output << source.getDay();

	return output;
}

BitcoinExchange::BitcoinExchange(void) {

}

BitcoinExchange::BitcoinExchange(BitcoinExchange &copy) {
	(void) copy;
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange &copy) {
	(void) copy;
	return *this;
}

BitcoinExchange::BitcoinExchange(std::string file) : input_file(file.c_str()) {
	std::ifstream data_file("data.csv");
	std::string data_line;

	if (!data_file.is_open() && !this->input_file.is_open())
		throw (std::invalid_argument("no data file and no input file"));
	if (!data_file.is_open())
		throw (std::invalid_argument("no data file"));
	if (!this->input_file.is_open())
		throw (std::invalid_argument("no input file"));

	while (std::getline(data_file, data_line)) {
		if (data_line == "date,exchange_rate")
			continue;
		double buffer_value = get_value(data_line);
		std::cout << buffer_value << std::endl;
		Date buffer_date(data_line);
		data.insert(std::map<Date, double>::value_type(buffer_date, buffer_value));
	}

	data_file.close();
}

BitcoinExchange::~BitcoinExchange() {

}

void BitcoinExchange::convert() {
	std::string input_line;

	while (std::getline(input_file, input_line)) {
		if (input_line == "date | value")
			continue;
		try {
			double buffer_value = get_value(input_line);
			if (buffer_value > 1000 || buffer_value < 0) {
				std::cout << "invalid value" << std::endl;
				continue;
			}
			Date buffer_date(input_line);
			std::cout << buffer_date << " => " << buffer_value << " = " << (double) buffer_value * data.upper_bound(buffer_date)->second <<  std::endl;
		} catch (std::exception& error) {
			std::cout << error.what() << std::endl;
			continue;
		}
	}
}