#include <map>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include "../include/parser.h"
#include "boost/algorithm/string.hpp"

std::map<std::string, std::vector<std::string>> Parser::getData(){
	/* returns a dictionary with  : 
	   key : the time 
	   value : a list of different concentration of protein mesured at that time */
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

std::vector<std::string> Parser::get_header() {
	std::ifstream file(fileName);
	std::vector<std::vector<std::string>> dataList;
	std::string line = "";
	
	// Iterate through each line and split the content using delimeter
	std::vector<std::string> header;
	getline(file, line) ; 
	boost::algorithm::split(header, line, boost::is_any_of(delimeter));

	header.erase(header.begin()) ; 
	return header ; 

}

std::string Parser::get_header_string() {
	std::vector<std::string> h = get_header() ; 
	std::string s = "";
	for (int i=0; i < h.size(); i++) {
		s += h[i] ; 
		s += " " ; 
	}
	return s ; 
}

std::vector<std::vector<std::string>> Parser::getData_nprot() {
	/* returns a dictionary with  : 
	   key : the time 
	   value : a list of different concentration of protein mesured at that time */
	std::ifstream file(fileName);
	std::vector<std::vector<std::string>> dataList;
	std::string line = "";
	
	// Iterate through each line and split the content using delimeter
	
	getline(file, line) ; 
	while (getline(file, line)){
		std::vector<std::string> vec;
		boost::algorithm::split(vec, line, boost::is_any_of(delimeter));
		dataList.push_back(vec) ; 
	}

	// Close the File
	file.close();
	return dataList;
}

std::vector<double> Parser::get_monomer_concentration() {
	std::ifstream file(fileName);
	std::vector<double> m ; 
	std::string line = ""; 
	while (getline(file, line)){;
		m.push_back(std::stod(line)) ; 
	}
	return m ;
}

