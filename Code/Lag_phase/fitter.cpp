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
	std::vector<double> tmp_tmp ;  

	for (int i = 0; i < results.size(); i++) {
		for (int j = 1; j < results[i].size()-1; j++) {
			int y_norm = (1 - relative_initial_concentration)*((std::stod(results[i][j]) - baseline)/ (plateau - baseline)) + relative_initial_concentration ; 
			tmp_tmp.push_back(y_norm) ; 
		}
		tmp.push_back(tmp_tmp) ; 
		
	}
	return tmp ; 
}