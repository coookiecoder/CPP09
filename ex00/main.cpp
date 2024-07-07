#include <BitcoinExchange.hpp>

int main(int argc, char** argv) {
	if (argc != 2)
		return (1);

	BitcoinExchange data(argv[1]);

	data.convert();
}