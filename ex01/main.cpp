#include "RPN.hpp"

int main(int ac, char** av){

    RPN rpn;

    if(ac != 2){
        std::cout << "Error: there must be 2 argument" << std::endl;
        return 0;
    }

    rpn.process(av[1]);
    std::cout << std::endl;
    return 2;
}