#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(){}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& copy) {
	*this = copy;
}

BitcoinExchange BitcoinExchange::operator=(const BitcoinExchange& copy) {
	this->data = copy.data;
	return *this; 
}

BitcoinExchange::~BitcoinExchange(){}

void BitcoinExchange::errorHandle(std::string error) {
	std::cout << "Error: " << error << std::endl;
	exit(1);
}

void BitcoinExchange::readData() {

	std::ifstream dataFile("data.csv");
	if (!dataFile) {
		errorHandle("the file doesn't exist");
	}

	std::string dataLine;

	std::getline(dataFile, dataLine);
	while (std::getline(dataFile, dataLine)) {
		std::istringstream ss(dataLine);
		
		std::string data_year, data_month, data_day;

		std::string date, value;
	
		if(std::getline(ss, date, ',')){
			
			std::stringstream iss(date);
			std::getline(iss, data_year, '-');
			std::getline(iss, data_month, '-');
			std::getline(iss, data_day, '-');

			int d_year = atoi(data_year.c_str());
			int d_month = atoi(data_month.c_str());
			int d_day = atoi(data_day.c_str());

			int data_combined = d_year * 10000 + d_month * 100 + d_day;
			if(std::getline(ss, value)){
				data[data_combined] = atof(value.c_str());
			}
		}
	}
	dataFile.close();
}
	//printMap(data);

bool BitcoinExchange::isNumber(std::string s){
	int flag = 0;
	for (std::string::size_type i = 0; i < s.length(); ++i){
		if (!isdigit(s[i]) && s[i] != '.') {
            return 1;
        }
		else if (s[i] == '.') {
			if (flag)
				return 1;
			flag++;
		}
 	}
    return 0;
}
bool BitcoinExchange::isAlpha(std::string s){
	for (std::string::size_type i = 0; i < s.length(); ++i){
		if(isalpha(s[i])){
			return 1;
		}
	}
	return 0;
}

bool BitcoinExchange::checkInput(std::string firstPart, double secondPart, std::string input){
	char separator = '|';
	size_t pipe = input.find(separator);

	std::string before_pipe = input.substr(0, input.find('|'));

	size_t after_pipe = input.find_first_not_of(" ", pipe + 1);

	std::string after_pipe_number = input.substr(pipe + 2);


	if(isAlpha(before_pipe)){
		std::cout << "Error: cannot be character after date" << std::endl;
		return 0;
	}
 	else if(pipe == std::string::npos){
		std::cout << "Error: invalid format" << std::endl;
		return 0;
	}
	else if(pipe != std::string::npos && after_pipe == std::string::npos){
		std::cout << "Error: must be value after separator" << std::endl;
		return 0;
	}
	else if(after_pipe == std::string::npos || input[after_pipe] == '-'){
		std::cout << "Error: must be positive number" << std::endl;
		return 0;
	}
    else if(after_pipe != std::string::npos && isNumber(after_pipe_number)){
		std::cout << "Error: must be number after separator" << std::endl;
		return 0;
	}

	std::istringstream iss(firstPart);
	std::string year_str, month_str, day_str;
	std::getline(iss, year_str, '-');
	std::getline(iss, month_str, '-');
	std::getline(iss, day_str, '-');

	int year = atoi(year_str.c_str());
	int month = atoi(month_str.c_str());
	int day = atoi(day_str.c_str());

	if(year < 2009 || year > 2023){
		std::cout << "Error: bad input => " << firstPart << std::endl;
		return 0;
	}
	if (!((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))){
		if (month == 2 && day == 29){
			std::cout << "Error: bad input => " << firstPart << std::endl;
			return 0;
		}
		else if (month == 2 && day > 29){
			std::cout << "Error: bad input => " << firstPart << std::endl;
			return 0;
		}
	}
	if (month == 2 && day > 29){
			std::cout << "Error: bad input => " << firstPart << std::endl;
			return 0;
		}

	if(month < 1 || month > 12){
		std::cout << "Error: bad input => " << firstPart << std::endl;
		return 0;
	}
	if((day < 1 || day > 31) || (year == 2009 && month == 1 && day < 2)){
		std::cout << "Error: bad input => " << firstPart << std::endl;
		return 0;
	}
	if (month == 4 || month == 6 || month == 9 || month == 11){
		if(day > 30){
			std::cout << "Error: bad input => " << firstPart << std::endl;
			return 0;
		}
	}

	if(!(typeid(double) == typeid(secondPart))){
		std::cout << "Error: value is not a digit" << std::endl;
		return 0;
	}
	else if(secondPart > 1000){
		std::cout << "Error: too large a number" << std::endl;
		return 0;
	}
	else if(secondPart < 0) {
		std::cout << "Error: not a positive number" << std::endl;
		return 0;
	}

	this->combined_date = year * 10000 + month * 100 + day;
	return 1;
}

void BitcoinExchange::readInput(const char* inputFile){
	std::ifstream inputfile(inputFile);
    if(!inputfile.is_open()){
        this->errorHandle("could not open this file");
    }
	std::string input;
	std::getline(inputfile, input);
	if(!(input == "date | value"))
		errorHandle("invalid file format");
	while(std::getline(inputfile, input)){
		try
		{
			std::istringstream iss(input);
			std::string firstPart;
			double secondPart;
			std::getline(iss, firstPart, '|');
			
			iss >> secondPart;
			bool res = checkInput(firstPart, secondPart, input);
			if (res)
				compareAndProcess(firstPart,secondPart);
		}
		catch(const std::exception& e)
		{
			if(e.what())
				std::cout << "Error: cannot be empty line" << std::endl;
		}
		
	}

}

void BitcoinExchange::compareAndProcess(std::string firstPart, double secondPart){

	for(dataIterator it = this->data.begin(); it != this->data.end(); ++it){
		if(it->first >= combined_date){
			if(it->first != combined_date){
				double res = (--it)->second * secondPart;
				std::cout << firstPart << " => " << secondPart << " = " << res << std::endl;
			}
			else
				std::cout << firstPart << " => " << secondPart << " = " << it->second * secondPart << std::endl;

			break;

		}
	}
}

/* void BitcoinExchange::printMap(std::map<int, double> &data){
	dataIterator it;
	for(it = data.begin(); it != data.end(); ++it){
		std::cout << it->first << " = " << it->second << std::endl; 

	}
	std::cout << "--------------" << std::endl;
} */

void BitcoinExchange::startBtc(const char* inputFile){
	readData();
	readInput(inputFile);
}