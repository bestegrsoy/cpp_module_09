#include "PmergeMe.hpp"

int main(int ac, char **av){
    (void)av;

    PmergeMe m;
    if(ac <= 1)
        m.errorHandle("you must give an argument");
    m.process(ac, av);
}