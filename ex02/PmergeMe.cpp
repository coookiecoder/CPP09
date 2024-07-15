#include "PmergeMe.hpp"

# define MICROSECOND 100000

unsigned int stou(const std::string& str)
{
	unsigned int num;
	std::stringstream ss(str);

	ss >> num;
	return num;
}

PmergeMe::PmergeMe(void) {

};

PmergeMe::PmergeMe(const PmergeMe& to_copy) {
	*this = to_copy;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& to_copy) {
	(void)to_copy;
	return *this;
}

PmergeMe::~PmergeMe(void) {

};

static void printVec(std::vector<unsigned int>& vec)
{
	std::vector<unsigned int>::const_iterator itr;
	for (itr = vec.begin(); itr != vec.end(); itr++)
		std::cout << *itr << " ";
	std::cout << std::endl;
}

static std::vector<unsigned int> mergeVecs(std::vector<unsigned int>& left, std::vector<unsigned int>& right)
{
	std::vector<unsigned int> result;

	// Merge the two vectors until one of them becomes empty
	while (!left.empty() && !right.empty())
	{
		if (left.front() <= right.front())
		{
			result.push_back(left.front());
			left.erase(left.begin());
		}
		else
		{
			result.push_back(right.front());
			right.erase(right.begin());
		}
	}

	// Add any remaining elements from the left vector
	while (!left.empty())
	{
		result.push_back(left.front());
		left.erase(left.begin());
	}

	// Add any remaining elements from the right vector
	while (!right.empty())
	{
		result.push_back(right.front());
		right.erase(right.begin());
	}
	return result;
}

static std::vector<unsigned int> mergeInsertVec(std::vector<unsigned int>& vec) {
	// Base case: a vector with zero or one elements is already sorted
	if (vec.size() <= 1) {
		return vec;
	}

	// Divide the vector into two halves
	int mid = vec.size() / 2;
	std::vector<unsigned int> left(vec.begin(), vec.begin() + mid);
	std::vector<unsigned int> right(vec.begin() + mid, vec.end());

	// Recursively sort the left and right halves
	left = mergeInsertVec(left);
	right = mergeInsertVec(right);

	// Merge the sorted halves
	return mergeVecs(left, right);
}

void PmergeMe::sortVec(int argc, char **argv)
{
	std::vector<unsigned int> storage;

	for (int i = 1; i < argc; i += 1) {
		storage.push_back(stou(argv[i]));
	}

	std::cout << "<vec>Before: ";
	printVec(storage);

	std::clock_t start = std::clock();

	storage = mergeInsertVec(storage);
	this->element = argc - 1;

	this->time_taken_vector = static_cast<double>(std::clock() - start) / static_cast<double>(CLOCKS_PER_SEC) * MICROSECOND;

	std::cout << "<vec>After: ";
	printVec(storage);
}

static void printList(std::list<unsigned int>& lst)
{
	std::list<unsigned int>::const_iterator itr;
	for (itr = lst.begin(); itr != lst.end(); itr++)
		std::cout << *itr << " ";
	std::cout << std::endl;
}

static std::list<unsigned int> mergeLists(std::list<unsigned int>& left, std::list<unsigned int>& right)
{
	std::list<unsigned int> result;

	// Merge the two vectors until one of them becomes empty
	while (!left.empty() && !right.empty())
	{
		if (left.front() <= right.front())
		{
			result.push_back(left.front());
			left.erase(left.begin());
		}
		else
		{
			result.push_back(right.front());
			right.erase(right.begin());
		}
	}

	// Add any remaining elements from the left vector
	while (!left.empty())
	{
		result.push_back(left.front());
		left.erase(left.begin());
	}

	// Add any remaining elements from the right vector
	while (!right.empty())
	{
		result.push_back(right.front());
		right.erase(right.begin());
	}
	return result;
}

static std::list<unsigned int> mergeInsertList(std::list<unsigned int>& lst) {
	// Base case: a list with zero or one elements is already sorted
	if (lst.size() <= 1) {
		return lst;
	}

	// Divide the list into two halves
	int mid = lst.size() / 2;
	std::list<unsigned int> left;
	std::list<unsigned int> right;

	for (int i = 0; i < mid; i++) {
		left.push_back(lst.front());
		lst.pop_front();
	}
	right = lst;

	// Recursively sort the left and right halves
	left = mergeInsertList(left);
	right = mergeInsertList(right);

	// Merge the sorted halves
	return mergeLists(left, right);
}

void PmergeMe::sortList(int argc, char **argv)
{
	std::list<unsigned int> storage;

	for (int i = 1; i < argc; i += 1)
		storage.push_back(stou(argv[i]));

	std::cout << "<list>Before: ";
	printList(storage);

	std::clock_t start = std::clock();

	storage = mergeInsertList(storage);

	this->time_taken_list = static_cast<double>(std::clock() - start) / static_cast<double>(CLOCKS_PER_SEC) * MICROSECOND;
	this->element = argc - 1;

	std::cout << "<list>After: ";
	printList(storage);
}

const char*	PmergeMe::InvalidElementException::what() const throw() {
	return "PmergeMe exception: invalid element";
}

void PmergeMe::show_time_list(void)
{
	std::cout << "Time to process a range of " << this->element << " elements ";
	std::cout << "with std::list<unsigned int> : " << this->time_taken_list << " µs" << std::endl;
}

void PmergeMe::show_time_vector()
{
	std::cout << "Time to process a range of " << this->element << " elements ";
	std::cout << "with std::vector<unsigned int> : " << this->time_taken_vector << " µs" << std::endl;
}