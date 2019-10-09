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
#include "boost/algorithm/string.hpp"

double Curve::calculate_mean(std::vector<double> y){
	double sum = 0;
	for(int i = 0; i < y.size(); i++)
		sum += y[i];
	
	return (sum / y.size());
}

double Curve::calculate_variance(std::vector<double> y, double mean){
	double temp = 0;
	for(int i = 0; i < y.size(); i++){
		temp += (y[i] - mean) * (y[i] - mean) ;
	}
	return temp / y.size();
}

double Curve::calculate_sample_variance(std::vector<double> y, double mean){
	double temp = 0;
	for(int i = 0; i < y.size(); i++){
		temp += (y[i] - mean) * (y[i] - mean) ;
	}
	return temp / (y.size() - 1);
}

double Curve::standard_deviation(std::vector<double> y, double mean){
	return sqrt(calculate_variance(y, mean));
}

double Curve::sample_standard_deviation(std::vector<double> y, double mean){
	return sqrt(calculate_sample_variance(y, mean));
}

double Curve::y_baseline(std::vector<double> y) {
	double mean = calculate_mean(y) ; 
	double std = standard_deviation(y, mean) ; 

	return mean - std ; 
}

double Curve::y_plateau(std::vector<double> y) {
	double mean = calculate_mean(y) ; 
	double std = standard_deviation(y, mean) ; 

	return mean + std ; 
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