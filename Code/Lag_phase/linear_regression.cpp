#include<iostream>
#include<cmath>
#include <vector>
#include "linear_regression.h"


std::vector<double> Linear_regression::linear_regression(std::vector<double> x,std::vector<double> y, int dataSize){

    std::vector<double> results ; 
    double SUMx = 0;        //sum of x values
    double SUMy = 0;        //sum of y values
    double SUMxy = 0;       //sum of x * y
    double SUMxx = 0;       //sum of x^2
    double SUMres = 0;      //sum of squared residue
    double res = 0;         //residue squared
    double slope = 0;       //slope of regression line
    double y_intercept = 0; //y intercept of regression line
    double SUM_Yres = 0;    //sum of squared of the discrepancies
    double AVGy = 0;        //mean of y
    double AVGx = 0;        //mean of x
    double Yres = 0;        //squared of the discrepancies
    double Rsqr = 0;        //coefficient of determination

   //calculate various sums 
    for (int i = 0; i < dataSize; i++){
        //sum of x
        SUMx += x[i];
        //sum of y
        SUMy += y[i];
        //sum of squared x*y
        SUMxy += x[i] * y[i];
        //sum of squared x
        SUMxx += x[i] * x[i];
    }

    //calculate the means of x and y
    AVGy = SUMy / dataSize;
    AVGx = SUMx / dataSize;

    //slope or a1
    slope = (dataSize * SUMxy - SUMx * SUMy) / (dataSize * SUMxx - SUMx*SUMx);

    //y itercept or a0
    y_intercept = AVGy - slope * AVGx;

    results.push_back(slope) ; 
    results.push_back(y_intercept) ;
    return results ;
}

std::vector<std::vector<double>> Linear_regression::get_predicted_values(std::vector<double> x, double slope, double y_intercept) {
    //calculate squared residues, their sum etc.
    std::vector<std::vector<double>> coord;  
    std::vector<double> x_coord ; 
    std::vector<double> y_coord ; 
    
    for (int i = 0; i < x.size(); i++) {
        x_coord.push_back(x[i]) ;
        y_coord.push_back((slope*x[i]) + y_intercept); 
    }
    coord.push_back(x_coord) ; coord.push_back(y_coord) ; 
    return coord ;
}

double Linear_regression::get_half_time(double slope, double y_intercept, double x) {
    double half_time = (slope*x) + y_intercept ; 

    return half_time ; 
}

void Linear_regression::display(std::vector<double> x_axis,std::vector<double> y_axis){
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
