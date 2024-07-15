#pragma once

#include <sstream>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <vector>
#include <list>
#include <exception>

unsigned int stou(const std::string& str);

class PmergeMe {
private:
	double time_taken_list;
	double time_taken_vector;
	int element;
public:
	PmergeMe(void);
	PmergeMe(const PmergeMe& to_copy);
	PmergeMe &operator=(const PmergeMe& to_copy);
	~PmergeMe(void);

	void sortVec(int argc, char **argv);
	void sortList(int argc, char **argv);

	void show_time_list(void);
	void show_time_vector(void);

	class InvalidElementException : public std::exception {
	public:
		virtual const char* what() const throw();
	};
};