#include "RPN.hpp"

RPN::RPN(){}
RPN::RPN(const RPN& copy){
	*this = copy;
}
RPN RPN::operator=(const RPN& copy){
	this->myStack = copy.myStack;
	return(*this);
}
RPN::~RPN(){}

void RPN::errorHandle(std::string error) {
	std::cout << "Error: " << error << std::endl;
	exit(1);
}

void RPN::process(char* arg){

	int res = 0;
	for(int i = 0; arg[i]; i++){
		if(arg[i] >= '0' && arg[i] <= '9'){
			this->myStack.push(arg[i] - '0');
			if (arg[i+1] >= '0' && arg[i+1] <= '9') {
				errorHandle("value must be between 0 - 9");
			}
		}
		if (arg[i] == '+' || arg[i] == '-' || arg[i] == '/' || arg[i] == '*') {
			if (this->myStack.size() < 2)
				errorHandle("stack is empty");
			int value1 = this->myStack.top();
			this->myStack.pop();
			if (this->myStack.empty())
				errorHandle("stack is empty");

			int value2 = this->myStack.top();
			this->myStack.pop();

			if(arg[i] == '+' ){
				res = value1 + value2;
			}
			else if(arg[i] == '-' ){
				res = value2 - value1;
			}
			else if(arg[i] == '*' ){
				res = value1 * value2;
			}
			else if(arg[i] == '/' ){
				if(value1 == 0 || value2 == 0){
					errorHandle("cannot divide by 0");
				}
				res = value2 / value1;
			}
			this->myStack.push(res);
		}
	}
	if (this->myStack.size() != 1)
		errorHandle("not enough operands");
	std::cout << res;
}
