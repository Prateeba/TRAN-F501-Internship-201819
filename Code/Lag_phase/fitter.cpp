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

std::vector<Curve> Fitter::normalize(std::vector<double> time_steps, int baseline, int relative_initial_concentration){
	/* Raw data preprocessing phase 
	 * Baseline value = average value of the data at the beseline 
	 * Plateau value = average value of the data at the plateau 
	*/
	std::vector<Curve> normalized_curves ;  
    for (int i = 0; i < curves.size(); i++) {
    	double y_p = curves[i].y_plateau(curves[i].get_y_axis()) ; 
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

std::vector<std::vector<double>> Fitter::extract_middle_part(Curve c) {
	// TO CHECK IF IT IS THE RIGHT WAY TO DO  .. 
	/* 
	 * Requires to know the monomer concentration for each repeat 
	 * Select the middle part of the curve -> Determine : 
			1) When the average over several points is first above 0.3 
			2) when the average is last below 0.7 
			3) The number of points to average over depends on the number of points in the curve 
	*/
	std::vector<std::vector<double>> coord;  

	std::vector<double> x = c.get_x_axis() ; 
	std::vector<double> y = c.get_y_axis() ; 

	std::vector<double> middle_x ; 
	std::vector<double> middle_y ;
	for (int i = 0; i < x.size(); i++) {
		if (x[i] >= 0.3 && x[i] <= 0.7) {
			middle_y.push_back(y[i]) ; 
			middle_x.push_back(x[i]) ; 
		}
	} 
	coord.push_back(middle_x) ; 
	coord.push_back(middle_y) ; 
	return coord ; 
}

double Fitter::extract_half_time(std::vector<double> x, std::vector<double> y) {
	/*
	 * Fit a straight line through the middle part of the curve 
			1) The point at which it crosses the value 0.5 is the HALF-TIME 
	*/
	Linear_regression L ; 
    std::vector<double> res = L.linear_regression(x,y,x.size()) ; 
    
    std::vector<double> test ;
    test.push_back(0) ; 
    for (int i = 0; i < x.size()-1; i++) {
    	test.push_back(i+0.5) ; 
    } 
    std::vector<std::vector<double>> coords = L.get_predicted_values(test, res[0], res[1]) ; 

    double half_time = L.get_half_time(res[0], res[1], 0.5) ; 

    //L.display(x, y) ;
    //L.display(coords[0], coords[1]) ; 

    return half_time ;

}