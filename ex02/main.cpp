#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>
#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	if (argc == 1)
		return EXIT_SUCCESS;
	PmergeMe pmm;

	try {
		for (int i = 1; i < argc; i += 1)
			if (std::string(argv[i]).find_first_not_of("0123456789") != std::string::npos)
				throw PmergeMe::InvalidElementException();

		std::vector<unsigned int>temp;
		for (int i = 1; i < argc; i += 1)
			temp.push_back(stou(argv[i]));

		std::vector<unsigned int>::iterator itr;
		std::vector<unsigned int>::iterator itr2;
		for (itr = temp.begin(); itr != temp.end(); itr++)
		{
			for (itr2 = itr + 1; itr2 != temp.end(); itr2++)
				if (*itr2 == *itr)
					throw PmergeMe::InvalidElementException();
		}
	}
	catch (std::exception& e) {
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}

	pmm.sortVec(argc, argv);
	std::cout << std::endl;
	pmm.sortList(argc, argv);
	pmm.show_time_list();
	pmm.show_time_vector();

	return EXIT_SUCCESS;
}
