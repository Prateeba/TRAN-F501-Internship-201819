#ifndef DEF_PARSER
#define DEF_PARSER
#include <iostream>
#include <cstddef>
#include <string>
#include <limits>
#include <vector>
#include <map>

/*
 * A class to read data from a csv file.
 */
class Parser{
private : 
	std::string fileName;
	std::string delimeter;
 
public:
	Parser(std::string filename, std::string delm = ";"):fileName(filename), delimeter(delm) {}
	
	// Function to fetch data from a CSV File
	std::map<std::string, std::vector<std::string>> getData();
	std::vector<std::vector<std::string>> getData_nprot() ; 
};


#endif