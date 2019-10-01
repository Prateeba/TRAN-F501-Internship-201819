#include <map>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include "parser.h"
#include "fitter.h"


int main(){
	/*Parser reader("thT_kinetics_2.csv");
 
	std::map<std::string, std::vector<std::string>> dataList = reader.getData();
	std::map<std::string, std::vector<std::string>>::iterator it=dataList.begin() ;
	for (it=dataList.begin(); it!=dataList.end(); ++it)
    	std::cout << it->first << " => " << it->second[0] << '\n'; */

    // --------------- Test for the nprot ---------------------------- 
    Parser reader_nprot("data/nprot.2016.010-S2.csv", "\t");
    std::vector<std::vector<std::string>> dataList_nprot = reader_nprot.getData_nprot() ; 

    /* plot raw data*/
    /*for (int i = 0; i < dataList_nprot.size(); i++) {
    	for (int j = 0; j < dataList_nprot[i].size(); j++) {
    		std::cout << dataList_nprot[i][j] << " " ; 
    	}
    	std::cout << "\n" ; 
    }*/

    /* Normalize data and plot */
    Fitter fitter(dataList_nprot) ;  
    std::vector<std::vector<double>> dataList_nprot_normalize = fitter.normalize(dataList_nprot,1,55,0) ; 

    /*for (int i = 0; i < dataList_nprot_normalize.size(); i++) {
        for (int j = 0; j < dataList_nprot_normalize[i].size(); j++) {
            std::cout << dataList_nprot_normalize[i][j] << " " ; 
        }
        std::cout << "\n" ; 
    }*/

    /* Merge similar curves -> Repeats of the same curve */

    std::vector<std::vector<double>> merged_nprot = fitter.merge(dataList_nprot_normalize) ; 
    for (int i = 0; i < merged_nprot.size(); i++) {
        for (int j = 0; j < merged_nprot.size(); j++) {
            std::cout << merged_nprot[i][j] << " " ; 
        }
        std::cout << "\n" ; 
    }

    /* Extract Half times*/ 
    /* Construct different models */ 
	
	return 0;
}