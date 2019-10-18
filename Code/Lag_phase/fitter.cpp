#include <map>
#include <math.h> 
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

std::vector<double> Fitter::half_time(std::vector<double> monomer_concentration, std::vector<Curve> normalized_curves) {
	/*
	 Requires : 	
	 	1) Normalized value of the ThT kinetics 
	 	2) Monomer concentration for each repeat
     Time at which the signal has reached its final plateau value
	*/
    std::vector<double> half_times ;  
    for (int i = 0; i < normalized_curves.size(); i++) {
    	std::vector<double> x = normalized_curves[i].get_x_axis() ; 
    	std::vector<double> y = normalized_curves[i].get_y_axis() ; 

		std::vector<double> fit_param = normalized_curves[i].fit(x,y) ;   
		double h_time = normalized_curves[i].get_halftime(fit_param) ; 
		half_times.push_back(h_time) ;  	
    }
    return half_times ; 
}

std::vector<std::vector<double>> Fitter::log_tau_vs_log_m_concentration(std::vector<double> monomer_concentration, std::vector<double> half_times) {
	/* 
	 * Compute log (time)
	 * Compute log (monomer concentration)
	*/ 
	std::vector<std::vector<double>> results ; 
	std::vector<double> log_x ;  // x-axis = monomer concentration 
	std::vector<double> log_y ;  // y-axis = half times 
	if (monomer_concentration.size() == half_times.size()) {
		for (int i = 0; i < monomer_concentration.size(); i++) {
			log_x.push_back(log(monomer_concentration[i])) ; 
			log_y.push_back(log(half_times[i])) ; 
		}
	}
	results.push_back(log_x) ; 
	results.push_back(log_y) ; 

	return results ; 
}

std::vector<std::vector<double>> Fitter::log_tau_vs_log_m_concentration_fit(std::vector<std::vector<double>> res) {
	Linear_regression L ; 
    std::vector<double> resL = L.linear_regression(res[0],res[1],res[0].size()) ;
   	std::vector<std::vector<double>> log_off_plot = L.get_predicted_values(res[0], resL[0], resL[1] ) ; 

   	return log_off_plot ; 
} 



 