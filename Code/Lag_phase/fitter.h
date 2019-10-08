#ifndef DEF_FITTER
#define DEF_FITTER
#include <iostream>
#include <cstddef>
#include "curve.h"
#include <string>
#include <limits>
#include <vector>
#include <map>


class Fitter {
private : 
	std::vector<Curve> curves  ; // contains the data 

public :
	Fitter(std::vector<Curve> c) : curves(c) {}
	std::vector<Curve> get_curves() {return curves ;}
	std::vector<Curve> normalize(std::vector<double>, int, int , int) ;  
	std::vector<Curve> merge(std::vector<double>, std::vector<Curve>, int) ; 
	Curve compute_mean(std::vector<double>, std::vector<std::vector<double>>, int) ; 
	void extract_half_time(std::vector<double> , std::vector<double> ) ; 
	std::vector<std::vector<double>> extract_middle_part(Curve c) ; 

} ; 

#endif 