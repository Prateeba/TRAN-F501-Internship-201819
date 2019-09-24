#include <map>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include "boost/algorithm/string.hpp"

/*
 * A class to read data from a csv file.
 */
class CSVReader{
private : 
	std::string fileName;
	std::string delimeter;
 
public:
	CSVReader(std::string filename, std::string delm = ";"):fileName(filename), delimeter(delm) {}
	// Function to fetch data from a CSV File
	std::map<std::string, std::vector<std::string>> getData();
};


std::map<std::string, std::vector<std::string>> CSVReader::getData(){
	std::ifstream file(fileName);
	std::map<std::string, std::vector<std::string>> dataList;
	std::string line = "";
	
	// Iterate through each line and split the content using delimeter
	while (getline(file, line)){
		std::vector<std::string> vec;
		boost::algorithm::split(vec, line, boost::is_any_of(delimeter));
		
		if (vec.size() >= 2)  {
			std::map<std::string, std::vector<std::string>>::iterator i = dataList.find(vec[0]) ; 
			if (i == dataList.end()) { 
				/* Not found -> insert */
				dataList.insert({vec[0], {}}) ;
				dataList[vec[0]].push_back(vec[1]) ; 
			}
			else { 
				/* Found -> populate vector */ 
				dataList[vec[0]].push_back(vec[1]) ; 
			}
		}

	}
	// Close the File
	file.close();
	return dataList;
}

int main(){
	// Creating an object of CSVWriter
	CSVReader reader("thT_kinetics_2.csv");
 
	// Get the data from CSV File
	std::map<std::string, std::vector<std::string>> dataList = reader.getData();

	std::map<std::string, std::vector<std::string>>::iterator it=dataList.begin() ;
	for (it=dataList.begin(); it!=dataList.end(); ++it)
    	std::cout << it->first << " => " << it->second[0] << '\n'; 
	
	return 0;
}
