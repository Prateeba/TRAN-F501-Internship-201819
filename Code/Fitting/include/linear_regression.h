#ifndef DEF_LINEAR_REGRESSION
#define DEF_LINEAR_REGRESSION
#include <iostream>
#include <cstddef>
#include "curve.h"
#include <string>
#include <limits>
#include <vector>
#include <map>

class Linear_regression{
private : 

public : 
	Linear_regression(){} 
	std::vector<double> linear_regression(std::vector<double>, std::vector<double>, int) ; 
	std::vector<std::vector<double>> get_predicted_values(std::vector<double>, double, double) ;  
	void display(std::vector<double>, std::vector<double>) ; 
} ; 

#endif