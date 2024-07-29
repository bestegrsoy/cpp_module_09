#include "PmergeMe.hpp"

PmergeMe::PmergeMe(){}
PmergeMe::PmergeMe(const PmergeMe& copy){
	*this = copy;
}
PmergeMe PmergeMe::operator=(const PmergeMe& copy){
	this->_vector = copy._vector;
	this->_list = copy._list;
	this->size = copy.size;
	return(*this);
}
PmergeMe::~PmergeMe(){};

void PmergeMe::errorHandle(std::string error){
	std::cout << "Error: " << error << std::endl;
	exit(1);
}

int PmergeMe::isNumber(char* str){
	for(size_t i = 0; i < strlen(str); ++i){
		if(!isdigit(str[i]))
			return 0;
	}
	return 1;
}

void PmergeMe::printTime(timeval start, timeval end, std::string type){
	double elapsed_time = ((double)end.tv_usec - (double)start.tv_usec) / 1000000;
	std::cout << "Time to process a range of " << this->size << " elements with " << type << " : " << 
		std::fixed << elapsed_time << " us"<< std::endl; 
}

template<typename T>
void PmergeMe::insertionSort(T& A, int start, int end){
	typename T::iterator it = A.begin();
	typename T::iterator ite = A.begin();
	for(int i = 0; i< start;++i){
		++it;
	}
	for(int i = 0; i< end+1; ++i){
		++ite;
	}
    while (it != ite && it != A.end())
	{
        typename T::iterator current = it;
        int temp = *it;
        typename T::iterator prev = it;
		typename T::iterator next = prev;
		++next;

        while (prev != A.begin() && *(--prev) > temp)
		{
            *current = *prev;
            current = prev;
        }
        *current = temp;
		current = next;
		++it;
    }
}



template<typename T>
void PmergeMe::merge(T& A, int start, int mid, int end){
	T left;
    T right;

    typename T::iterator it = A.begin();
    for(int i = 0; i< start; ++i){
		++it;
	}

    for (int i = start; i <= mid; ++i) {
        left.push_back(*it);
        ++it;
    }

    it = A.begin();
 	for(int i = 0; i < mid+1; ++i){
		++it;
	}
    for (int i = mid + 1; i <= end; ++i) {
        right.push_back(*it);
        ++it;
    }

    typename T::iterator leftIt = left.begin();
    typename T::iterator rightIt = right.begin();
    typename T::iterator mergedIt = A.begin();
    for(int i = 0; i< start; ++i){
		++mergedIt;
	}

    while (leftIt != left.end() && rightIt != right.end())
	{
        if (*leftIt <= *rightIt) {
            *mergedIt = *leftIt;
            ++leftIt;
        } else {
            *mergedIt = *rightIt;
            ++rightIt;
        }
        ++mergedIt;
    }

    for (;leftIt != left.end(); ++leftIt, ++mergedIt) {
        *mergedIt = *leftIt;
    }

    for (;rightIt != right.end(); ++rightIt, ++mergedIt) {
        *mergedIt = *rightIt;
    }
}

template<typename T>
void PmergeMe::mergeInsert(T& A, int start, int end){
	if(end - start > THRESHOLD){
		int mid = (start + end) / 2;
		mergeInsert(A, start, mid);
		mergeInsert(A, mid + 1, end);
		merge(A, start, mid, end);
	}
	else{
		insertionSort(A, start, end);
	}
}


void PmergeMe::checkArg(int ac, char** av){

	int number;
	for(int i = 1; i < ac; i++){
		if(!isNumber(av[i]))
			errorHandle("value must be integer");
		number = atoi(av[i]);
		if(number < 0)
			errorHandle("value must be positive integer");
		_vector.push_back(number);
		_list.push_back(number);
	}
	std::cout << "Before:   ";
	for(int i = 1; i < ac; i++){
		if(ac >= 7 && i == 5){
			std::cout << "[...]";
			break;
		}
		std::cout << av[i] << " ";
	}
	std::cout << std::endl;
	this->size = ac - 1;
}


void PmergeMe::process(int ac, char** av){
	
	checkArg(ac, av);
	
	struct timeval start, end;
	gettimeofday(&start, 0);

	mergeInsert(this->_list, 0, this->_list.size() - 1);
	gettimeofday(&end, 0);
	std::cout << "After:	  ";
	int i = 0;
	for(std::list<int>::iterator it = this->_list.begin(); it != this->_list.end(); ++it){
		if(ac >= 7 && i == 4){
			std::cout << "[...]";
			break;
		}
		std::cout << *it << " ";
		++i;
	}
	std::cout << std::endl;
	printTime(start, end, "std::list");
	

	gettimeofday(&start, 0); 
	mergeInsert(this->_vector, 0, this->_vector.size() - 1);
	gettimeofday(&end, 0);
	printTime(start, end, "std::vector");
	
}
