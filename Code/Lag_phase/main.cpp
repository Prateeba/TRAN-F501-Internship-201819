#include <map>
#include <Rcpp.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include "parser.h"
#include "fitter.h"
#include "curve.h"


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
    /*for (int i = 0; i < curves.size(); i++) {
        curves[i].display() ;   
    }  ------- in comment but ok */

    /* Normalize data and plot */
    Fitter fitter(curves) ; 
    std::vector<Curve> normalized_curves = fitter.normalize(time_steps, 0, 200, 0.55) ; 
    /*for (int i = 0; i < normalized_curves.size(); i++) {
        normalized_curves[i].display() ;   
    }*/


    /* Merge similar curves -> Repeats of the same curve */
    std::vector<Curve> merged = fitter.merge(time_steps, normalized_curves, 4) ; 
    for (int i = 0; i < merged.size(); i++) {
        merged[i].display() ;   
    }  


    //std::vector<std::vector<double>> merged_nprot = fitter.merge(dataList_nprot_normalize) ; 
    /*for (int i = 0; i < merged_nprot.size(); i++) {
        for (int j = 0; j < merged_nprot.size(); j++) {
            std::cout << merged_nprot[i][j] << " " ; 
        }
        std::cout << "\n" ; 
    }*/

    /* Extract Half times*/ 
    /* Construct different models */ 


	
	return 0;
}