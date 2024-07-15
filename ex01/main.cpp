#include "RPN.hpp"

#include <stdexcept>
#include <iostream>

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "invalid argument" << std::endl;
		return (1);
	}

	RPN expression(argv[1]);
	try {
		std::cout << expression.evaluate();
	} catch (std::exception &error) {
		std::cerr << error.what() << std::endl;
	}
}
