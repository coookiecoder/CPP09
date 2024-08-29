#include <stdexcept>

#include <BitcoinExchange.hpp>

int main(int argc, char** argv) {
	if (argc != 2)
		return (1);

	try {
		BitcoinExchange data(argv[1]);
		data.convert();
	} catch (std::exception) {
		std::cerr << "data or input file not found" << std::endl;
		return (1);
	}
}
