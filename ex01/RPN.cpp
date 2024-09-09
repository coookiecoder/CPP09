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

float RPN::evaluate(void) {
	std::stack<float> number;
	float old = 0;
	float number_buffer = 0;
	std::string buffer;
	
	this->data >> buffer;
	while (this->data.rdbuf()->in_avail()) {
		if (buffer.length() > 1)
			throw (std::invalid_argument("error in the decoding of the RPN expression (invlalid number or operator)"));
		if (std::isdigit(buffer[0]))
			number.push(buffer[0] - '0');
		else if (buffer[0] == '+') {
			if (number.size() < 2)
				throw(std::invalid_argument("missing number"));
			number_buffer = number.top();
			old = number.top();
			number.pop();
			number_buffer = number.top() + number_buffer;
			if (number_buffer - old != number.top())
				throw (std::invalid_argument("overflow / underflow"));
			number.pop();
			number.push(number_buffer);
			std::cout << number_buffer << std::endl;
		}
		else if (buffer[0] == '-') {
			if (number.size() < 2)
				throw(std::invalid_argument("missing number"));
			number_buffer = number.top();
			old = number.top();
			number.pop();
			number_buffer = number.top() - number_buffer;
			if (number_buffer + old != number.top())
				throw (std::invalid_argument("overflow / underflow"));
			number.pop();
			number.push(number_buffer);
			std::cout << number_buffer << std::endl;
		}
		else if (buffer[0] == '*') {
			if (number.size() < 2)
				throw(std::invalid_argument("missing number"));
			number_buffer = number.top();
			old = number.top();
			number.pop();
			number_buffer = number.top() * number_buffer;
			if (number_buffer / old != number.top())
				throw (std::invalid_argument("overflow / underflow"));
			number.pop();
			number.push(number_buffer);
			std::cout << number_buffer << std::endl;
		}
		else if (buffer[0] == '/') {
			if (number.size() < 2)
				throw(std::invalid_argument("missing number"));
			number_buffer = number.top();
			old = number.top();
			number.pop();
			number_buffer = number.top() / number_buffer;
			if (number_buffer * old != number.top())
				throw (std::invalid_argument("overflow / underflow"));
			number.pop();
			number.push(number_buffer);
			std::cout << number_buffer << std::endl;
		}
		else
			throw (std::invalid_argument("error in the decoding of the RPN expression (invalide char input)"));
	
		this->data >> buffer;
	}

	if (number.size() > 1)
		throw (std::invalid_argument("error in the decoding of the RPN expression (missing operator)"));

	return (number.top());
}
