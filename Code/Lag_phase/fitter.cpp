#include <map>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include "fitter.h"
#include "boost/algorithm/string.hpp"

std::vector<std::vector<double>> Fitter::normalize(std::vector<std::vector<std::string>> results, int baseline, int plateau, int relative_initial_concentration){
	/* Raw data preprocessing phase */
	std::vector<std::vector<double>> tmp ;
	for (int i = 0; i < results.size(); i++) {
		std::vector<double> tmp_tmp ;  
		tmp_tmp.push_back(std::stod(results[i][0])) ;    // push time 
		for (int j = 1; j < results[i].size()-1; j++) {
			double y_norm = (1 - relative_initial_concentration)*((std::stod(results[i][j]) - baseline)/ (plateau - baseline)) + relative_initial_concentration ; 
			tmp_tmp.push_back(y_norm) ; 
		}
		tmp.push_back(tmp_tmp) ; 
		
	}
	return tmp ; 
}

std::vector<std::vector<double>> Fitter::merge(std::vector<std::vector<double>> normalized){
	int offset = 4 ; 
	std::vector<std::vector<double>> tmp ;
	// To do -> correct 
	for (int i = 0; i < normalized.size(); i++){
		std::vector<double> tmp_tmp ;
		tmp_tmp.push_back(normalized[i][0]) ;    // push time 
		
		for (int j = 1; j < normalized[i].size()-1 ;  j+= offset) { 
			tmp_tmp.push_back(normalized[i][j]) ; 
		}
		tmp.push_back(tmp_tmp) ; 
	}
	return tmp ; 
}

void Fitter::extract_half_time(std::vector<std::vector<double>> merged_curves) {

}