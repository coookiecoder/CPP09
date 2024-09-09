#pragma once

#include <stack>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <cctype>

class RPN {
private:
	std::stringstream data;
public:
	RPN(void);
	RPN(char *expression);
	RPN(RPN & copy);
	~RPN(void);

	RPN& operator=(RPN & copy);

	float evaluate(void);	
};
