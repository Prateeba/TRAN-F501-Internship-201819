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
	double mean(std::vector<double>, int, int, int) ;
	double mean(std::vector<double>, int, int) ; 
	std::vector<double> smooth_mean(std::vector<double>, int) ; 
	std::vector<double> which(std::vector<double>) ; 

public : 
	Curve(std::vector<double> x, std::vector<double> y) : x_axis(x), y_axis(y) {}
	std::vector<double> get_x_axis() {return x_axis ; }
	std::vector<double> get_y_axis() {return y_axis ; }
	double y_baseline(std::vector<double>, int) ; 
	double y_plateau(std::vector<double>, int) ; 
	std::vector<double> normalize(int, int, int) ; 
	std::vector<double> fit(std::vector<double>, std::vector<double>) ;
	double get_halftime(std::vector<double>) ;  
	std::string display() ; 

}; 

#endif