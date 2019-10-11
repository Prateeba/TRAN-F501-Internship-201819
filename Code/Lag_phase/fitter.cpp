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
#include "linear_regression.h"
#include "boost/algorithm/string.hpp"

std::vector<Curve> Fitter::normalize(std::vector<double> time_steps, int baseline, int plateau, int relative_initial_concentration){
	/* Raw data preprocessing phase 
	 * Baseline value = average value of the data at the beseline 
	 * Plateau value = average value of the data at the plateau 
	*/
	std::vector<Curve> normalized_curves ;  
    for (int i = 0; i < curves.size(); i++) {
    	double y_p = curves[i].y_plateau(curves[i].get_y_axis(), plateau) ; 
        Curve c(time_steps, curves[i].normalize(baseline, y_p, relative_initial_concentration)) ; 
        normalized_curves.push_back(c) ;  
    }
    return normalized_curves ; 
}

std::vector<Curve> Fitter::merge(std::vector<double> time_steps, std::vector<Curve> c, int repeats){
	/* Loop over each 4 repeats and compute the average data*/
	std::vector<Curve> merged ;

	for (int i = 0; i < c.size(); i+= repeats){ 
		std::vector<std::vector<double>> m ; 
		for (int j = 0; j < repeats ; j++) { 
			m.push_back(c[i+j].get_y_axis()) ;  
		}
		merged.push_back(compute_mean(time_steps, m, repeats)) ; 
	}
	return merged ; 
}

Curve Fitter::compute_mean(std::vector<double> time_steps, std::vector<std::vector<double>> m, int repeats) {
	std::vector<double> tmp ; 
	int max = m[0].size() ; 
	for (int j = 0; j < max; j++) {
		double res = 0.0 ; 
		for (int i = 0; i < m.size(); i++) {
			res += m[i][j] ; 
		}
		tmp.push_back((res/repeats)) ; 
	} 
	
	Curve c(time_steps, tmp) ; 
	return c ; 
}

std::vector<double> Fitter::half_time(std::vector<Curve> normalized_curves) {
	/*
	 * Fit a straight line through the middle part of the curve 
			1) The point at which it crosses the value 0.5 is the HALF-TIME 
	*/
    std::vector<double> half_times ;  
    for (int i = 0; i < normalized_curves.size(); i++) {
    	std::vector<double> x = normalized_curves[i].get_x_axis() ; 
    	std::vector<double> y = normalized_curves[i].get_y_axis() ; 

		std::vector<double> fit_param = normalized_curves[i].fit(x,y) ;   
		double h_time = normalized_curves[i].get_halftime(fit_param) ; 

		std::cout << "Half time : " << h_time <<std::endl ; 
		half_times.push_back(h_time) ;  	
    }
    return half_times ; 
}