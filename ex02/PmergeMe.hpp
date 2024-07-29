#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <set>
#include <sys/time.h>
//#include <iomanip>
//#include <cstring>
//#include <cstdlib>

#define THRESHOLD 5

class PmergeMe{

    private:
        std::vector<int> _vector;
        std::list<int> _list;
        size_t size;
    public:
        PmergeMe();
        PmergeMe(const PmergeMe& copy);
        PmergeMe operator=(const PmergeMe& copy);
        ~PmergeMe();

        void errorHandle(std::string error);
        void process(int ac, char** av);
        void checkArg(int ac, char** av);
        int isNumber(char* str);
        void printTime(timeval start, timeval end, std::string type);
        
        template<typename T>
        void mergeInsert(T& A, int start, int end);
        template<typename T>
        void insertionSort(T& A, int start, int end);
        template<typename T>
        void merge(T& A, int start, int mid, int end);
};

#endif