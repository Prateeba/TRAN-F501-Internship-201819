#include <map>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include "parser.h"
#include "fitter.h"
#include "curve.h"
#include "linear_regression.h"

int main(){

    // --------------- Test for the nprot ---------------------------- *
    /* Parse data file */
    Parser reader_nprot("data/nprot.2016.010-S2.csv", "\t");
    std::vector<std::vector<std::string>> dataList_nprot = reader_nprot.getData_nprot() ; 

    /* Create curve objects */
    std::vector<Curve> curves ; 
    std::vector<double> time_steps ; 
    for (int i = 0; i < dataList_nprot.size(); i++) {
    	time_steps.push_back(std::stod(dataList_nprot[i][0])) ; 	
    } 

    for (int i = 1; i < dataList_nprot[i].size(); i++) {
    	std::vector<double> tht_data ; 
    	for (int j = 0; j < dataList_nprot.size(); j++) {
    		tht_data.push_back(std::stod(dataList_nprot[j][i])) ; 
    	}
        Curve c(time_steps, tht_data) ; 
        curves.push_back(c) ;  
    }

    /* plot raw data -> to pipe through python script*/
    for (int i = 0; i < curves.size(); i++) {
        curves[i].display() ;   
    }

    std::vector<std::string> header = reader_nprot.get_header() ; 
    for (int i = 0; i < header.size(); i++) {
    	std::cout << header[i] << " " ; 
    }


    /* Normalize data and plot */
    Fitter fitter(curves) ; 
    std::vector<Curve> normalized_curves = fitter.normalize(time_steps, 0, 200, 0) ; 
    /*for (int i = 0; i < normalized_curves.size(); i++) {
        normalized_curves[i].display() ;   
    }*/

    

    /* Extract Half times*/ 
    // hypothetic monomer concentration 
    std::vector<double> m_concentration {50, 50, 50, 50, 40, 40, 40, 40, 35, 35, 35, 35, 30, 30, 30, 30, 25, 25, 25, 25, 20, 20, 20, 20, 17, 17, 17, 17, 15, 15, 15, 15, 13, 13, 13, 13, 11, 11, 11, 11} ; 
    std::vector<double> half_times = fitter.half_time(m_concentration, normalized_curves) ; 

    /* Log(half time) versus Log(monomer concentration) plot */
    std::vector<std::vector<double>> vs_plot = fitter.log_tau_vs_log_m_concentration(m_concentration, half_times) ;      // scatter points 
    std::vector<std::vector<double>> vs_plot_fit = fitter.log_tau_vs_log_m_concentration_fit(vs_plot) ;                  // straight line fit .



    /* Construct different models according to the scaling exponent and type of curvature */ 
    

	
	return 0;
}