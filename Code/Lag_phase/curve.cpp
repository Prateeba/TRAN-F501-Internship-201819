#include <map>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <math.h>
#include <algorithm>
#include "curve.h"
#include "linear_regression.h" 
#include "boost/algorithm/string.hpp"

double Curve::mean(std::vector<double> y, int begin, int end, int naverage){
	double sum = 0;
	for(int i = begin; i <= end; i++)
		sum += y[i];
	return (sum / naverage);
}

double Curve::mean(std::vector<double> y, int begin, int end){
	double sum = 0;
	int count = 0; 
	for(int i = begin; i <= end; i++) {
		sum += y[i];
		count ++ ; 
	}
	return (sum / count);
}

std::vector<double> Curve::smooth_mean(std::vector<double> vec, int naverage) {
	std::vector<double> nvec ; 
	int size_nvec = 0 ; 
	for (int i = 0; i < vec.size(); i++) {
		nvec.push_back(vec[i]) ; 
	}
	for (int i = 1; i <= vec.size(); i++) {
		if (i % naverage == 0) { // is a multiple 
			double m = mean(vec, (i-naverage+1)-1, i-1, naverage) ; 
			for (int j = i-naverage+1; j <= i; j++){
				nvec[j-1] = m ; 
				size_nvec ++ ; 
			}
		}
	}
	int i = vec.size()-1 ; 
    int ni = size_nvec ; 
    if(ni < i){
    	double m = mean(vec, (ni+1)-1, i) ; 
    	for (int k = (ni+1)-1 ; k <= i ; k++) {
			nvec[k] = m ; 
		}
    }
	return nvec ; 
}

std::vector<double> Curve::which(std::vector<double> nvec) {
	/* Return the index of the data to observe */
	std::vector<double> index ; 
	for (int i = 0; i < nvec.size(); i++) {
		if (nvec[i] >= 0.3 && nvec[i] <= 0.7) {
			index.push_back(i) ; 
		}
	}
	return index ; 
}


double Curve::y_baseline(std::vector<double> y, int baseline) {
	double sum = 0; 
	for (int i = 0; i < baseline; i++) {
		sum += y[i] ; 
	}
	if (baseline > 0) {
		sum = sum/baseline ; 
	}
	return sum ; 
}

double Curve::y_plateau(std::vector<double> y, int plateau) {
	double sum = 0; 
	for (int i = 0; i < plateau; i++) {
		sum += y[y.size()-i] ;  
	}
	if (plateau > 0) {
		sum = sum/plateau ; 
	}
	return sum ; 
}

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
		normalized_y_axis.push_back(y_norm) ; 
	}
	return normalized_y_axis ; 
}

std::vector<double> Curve::fit(std::vector<double> time, std::vector<double> normalized_val) {
	std::vector<double> smooth = smooth_mean(normalized_val, 2) ; 	
	std::vector<double> res = which(smooth) ; 

	std::vector<double> x; 
	std::vector<double> y; 
	
	for (int i = 0 ; i < res.size(); i ++) {
		x.push_back(time[res[i]]) ; 
		y.push_back(normalized_val[res[i]]) ; 
	}

	Linear_regression L ; 
    std::vector<double> resL = L.linear_regression(x,y,x.size()) ;
    return resL ; 
}


double Curve::get_halftime(std::vector<double> resL) {
	return (0.5-resL[1])/resL[0] ; 
}