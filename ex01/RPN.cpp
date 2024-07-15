#include "RPN.hpp"
#include <stdexcept>

RPN::RPN(void) {

}

RPN::RPN(char * expression) {
	this->data << expression << " END";
}

RPN::RPN(RPN & copy) {
	this->data << copy.data.rdbuf();
}

RPN::~RPN(void) {
	
}

RPN & RPN::operator=(RPN & copy) {
	this->data << copy.data.rdbuf();
	return (*this);
}

long long int RPN::evaluate(void) {
	std::stack<short> number;
	long long int result = 0;
	long long int old = result;
	std::string buffer;
	bool first = true;
	
	
	this->data >> buffer;
	while (this->data.rdbuf()->in_avail()) {
		if (buffer.length() > 1)
			throw (std::invalid_argument("error in the decoding of the RPN expression (invlalid number or operator)"));
		if (std::isdigit(buffer[0]))
			number.push(buffer[0] - '0');
		else if (buffer[0] == '-') {
			if (first) {
				result = number.top();
				number.pop();
				first = false;
			}
			old = result;
			result -= number.top();
			if (result + number.top() != old)
				throw (std::invalid_argument("overflow / underflow"));
			number.pop();
		}
		else if (buffer[0] == '+') {
			if (first) {
				result = number.top();
				number.pop();
				first = false;
			}
			old = result;
			result += number.top();
			if (result - number.top() != old)
				throw (std::invalid_argument("overflow / underflow"));
			number.pop();
		}
		else if (buffer[0] == '*') {
			if (first) {
				result = number.top();
				number.pop();
				first = false;
			}
			old = result;
			result *= number.top();
			if (result / number.top() != old)
				throw (std::invalid_argument("overflow / underflow"));
			number.pop();
		}
		else if (buffer[0] == '/') {
			if (first) {
				result = number.top();
				number.pop();
				first = false;
			}
			old = result;
			result /= number.top();
			if (result * number.top() != old)
				throw (std::invalid_argument("overflow / underflow"));
			number.pop();	
		}
		else
			throw (std::invalid_argument("error in the decoding of the RPN expression (invalide char input)"));
	
		this->data >> buffer;
	}

	if (!number.empty())
		throw (std::invalid_argument("error in the decoding of the RPN expression (missing operator)"));

	return (result);
}
