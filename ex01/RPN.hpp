#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <stack>
#include <cstdlib>


class RPN{

	private:
		std::stack<int> myStack;
	public:
		RPN();
		RPN(const RPN& copy);
		RPN operator=(const RPN& copy);
		~RPN();

		void process(char* arg);
		void errorHandle(std::string error);
};

#endif