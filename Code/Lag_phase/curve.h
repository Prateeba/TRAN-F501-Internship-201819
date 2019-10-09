#ifndef DEF_CURVE
#define DEF_CURVE
#include <iostream>
#include <cstddef>
#include <string>
#include <limits>
#include <vector>
#include <map>

class Curve{
private : 
	std::vector<double> x_axis ; // timestep 
	std::vector<double> y_axis ; // ThT kinetics 
	double calculate_mean(std::vector<double>) ; 
	double calculate_variance(std::vector<double>, double) ; 
	double calculate_sample_variance(std::vector<double>, double) ; 
	double standard_deviation(std::vector<double>, double) ; 
	double sample_standard_deviation(std::vector<double>, double) ; 

public : 
	Curve(std::vector<double> x, std::vector<double> y) : x_axis(x), y_axis(y) {}
	std::vector<double> get_x_axis() {return x_axis ; }
	std::vector<double> get_y_axis() {return y_axis ; }
	double y_baseline(std::vector<double>) ; 
	double y_plateau(std::vector<double>) ; 
	void display() ; 
	std::vector<double> normalize(int, int, int) ; 

}; 

#endif