#include <map>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include "curve.h"
#include "boost/algorithm/string.hpp"


void Curve::display() {
	std::vector<double> x_axis = this->get_x_axis() ; 
	std::vector<double> y_axis = this->get_y_axis() ; 

	if (x_axis.size() == y_axis.size()) {
		for (int i = 0; i < x_axis.size()-1 ; i++) {
			std::cout << x_axis[i]  << " ";  
		}
		std::cout << x_axis[x_axis.size()-1] << " => " ; 
	
		for (int i = 0;  i < y_axis.size()-1; i++) {
			std::cout << y_axis[i] << " ";
		}

		std::cout << y_axis[y_axis.size()-1] << "\n" ;
	}
}

std::vector<double> Curve::normalize(int baseline, int plateau, int relative_initial_concentration) {
	std::vector<double> normalized_y_axis ; 
	std::vector<double> y_axis = this->get_y_axis() ; 

	for (int i = 0; i < y_axis.size(); i++) {
		double y_norm = (1 - relative_initial_concentration)*((y_axis[i] - baseline)/(plateau - baseline)) + relative_initial_concentration ;  
		normalized_y_axis.push_back(y_norm/100) ; 
	}

	return normalized_y_axis ; 
}