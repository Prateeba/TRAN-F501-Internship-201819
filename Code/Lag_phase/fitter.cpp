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

std::vector<Curve> Fitter::normalize(std::vector<double> time_steps, int baseline, int plateau, int relative_initial_concentration){
	/* Raw data preprocessing phase 
	 * Baseline value = average value of the data at the beseline 
	 * Plateau value = average value of the data at the plateau 
	*/
	std::vector<Curve> normalized_curves ;  
    for (int i = 0; i < curves.size(); i++) {
        Curve c(time_steps, curves[i].normalize(baseline, plateau, relative_initial_concentration)) ; 
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
		tmp.push_back(res/repeats) ; 
	} 
	
	Curve c(time_steps, tmp) ; 
	return c ; 
}

void Fitter::extract_half_time(Curve c) {
	/**
	 * Requires to know the monomer concentration for each repeat 
	 * Select the middle part of the curve -> Determine : 
			1) When the average over several points is first above 0.3 
			2) when the average is last below 0.7 
			3) The number of points to average over depends on the number of points in the curve 

	 * Fit a straight line through the middle part of the curve 
			1) The point at which it crosses the value 0.5 is the HALF-TIME 
	*/
	std::vector<double> time = c.get_x_axis() ; 
	std::vector<double> val = c.get_y_axis() ; 

    /*val.smoothed <- smooth.mean(val, ceiling(length(val)/100))
    lm.D9 <- lm(val ~ time, subset=(which(0.3<=val.smoothed & val.smoothed<=0.7)))
    return( (0.5 - lm.D9$coefficients[1]) / lm.D9$coefficients[2])*/

}