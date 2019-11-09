#include <map>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <fstream>
#include <algorithm>
#include "../include/parser.h"
#include "../include/fitter.h"
#include "../include/curve.h"
#include "../include/linear_regression.h"

int main(int argc, char *argv[]) {
	if (argc <= 2 ) {
		std::cout << "Please enter : \n 1.The data path \n 2.Followed by the path to the initial monomer concentration for each curve \n 3.Followed by -n if the data is already normalized " << std::endl ; 
	}

	else {
	    /* Parse data file */
	    Parser reader_nprot(argv[1], "\t");
	    std::vector<std::vector<std::string>> dataList_nprot = reader_nprot.getData_nprot() ;  

	    /* Create curve objects */
	    std::vector<Curve> curves ; 
	    std::vector<double> time_steps ; 
	    for (int i = 0; i < dataList_nprot.size(); i++) {
	    	time_steps.push_back(std::stod(dataList_nprot[i][0])) ; 	
	    } 
	    std::ofstream raw;
		raw.open("./results/raw_data.txt");
		raw << reader_nprot.get_header_string() ; 
	    for (int i = 1; i < dataList_nprot[i].size(); i++) {
	    	std::vector<double> tht_data ; 
	    	for (int j = 0; j < dataList_nprot.size(); j++) {
	    		tht_data.push_back(std::stod(dataList_nprot[j][i])) ; 
	    	}
	        Curve c(time_steps, tht_data) ; 
	        raw << c.display() ;
	        curves.push_back(c) ;  
	    }
	    raw.close() ; 
	    Fitter fitter(curves) ; 

	    /* Parse the monomer concentration file */
	    Parser reader_nprot_m(argv[2]);
	    std::vector<double> m_concentration = reader_nprot_m.get_monomer_concentration() ; 

	    /* Extract scaling exponent */
	    double scaling_exp ; 
	    if (argc == 4) {
	    	std::string n = argv[3] ; 
		    /* Data is normalised -> only need to extract the scaling exponent */
		    if (n.compare("-n") == 0) {
		    	/* Extract Half times*/ 
			    // hypothetic monomer concentration 
			    std::vector<double> half_times = fitter.half_time(m_concentration, curves) ; 

			    /* Log(half time) versus Log(monomer concentration) plot */
			    Curve vs_plot = fitter.log_tau_vs_log_m_concentration(m_concentration, half_times) ;      // scatter points 
			    Curve vs_plot_fit = fitter.log_tau_vs_log_m_concentration_fit(vs_plot) ;                  // straight line fit

			    scaling_exp = fitter.get_scaling_exponent(vs_plot) ;  // The scaling exponent  

			    /* Save results */
			    std::ofstream log_off;
			    log_off.open("../results/vs_plot.txt");
			    log_off << vs_plot.display() ;
			    log_off << vs_plot_fit.display() ;   
			    log_off.close();
		    }
		}
		else {
			/* Normalize data and plot */    
			std::vector<Curve> normalized_curves = fitter.normalize(time_steps, 0, 200, 0) ; 
			std::ofstream norm;
				    
			norm.open("./results/normalized.txt");
			for (int i = 0; i < normalized_curves.size(); i++) {
				norm << normalized_curves[i].display() ;   
			}
			norm.close();
				    
			/* Extract Half times*/ 
			std::vector<double> half_times = fitter.half_time(m_concentration, normalized_curves) ; 

			/* Log(half time) versus Log(monomer concentration) plot */
			Curve vs_plot = fitter.log_tau_vs_log_m_concentration(m_concentration, half_times) ;      // scatter points 
			Curve vs_plot_fit = fitter.log_tau_vs_log_m_concentration_fit(vs_plot) ;                  // straight line fit

			scaling_exp = fitter.get_scaling_exponent(vs_plot) ;  // The scaling exponent  

			/* Save results */
			std::ofstream log_off;
			log_off.open("./results/vs_plot.txt");
			log_off << scaling_exp ; log_off << "\n" ; 
			log_off << vs_plot.display() ;
			log_off << vs_plot_fit.display() ;   
			log_off.close();
		}

		/* PLOTS */ 

		/* plot raw data */
	    std::string filename = "src/plot_raw.py";
	    std::string command = "python ";
	    command += filename;
	    system(command.c_str()); 

	    /* plot normalized data */
	    std::string filename1 = "src/plot_norm.py";
	    std::string command1 = "python ";
	    command1 += filename1;
	    system(command1.c_str()); 

	    /* Half-time versus monomer concentration */
	    std::string filename2 = "src/log_plot.py";
	    std::string command2 = "python ";
	    command2 += filename2;
	    system(command2.c_str()); 


	    /* Construct different models according to the scaling exponent and type of curvature */ 
	    if (scaling_exp < -1 ) {
	        std::cout << "The appropriate model would be the Secondary nucleation " << std::endl ; 
	        // Call the appropriate python script to fit the different parameters 
	        // Save the parameters in a file again 
	        // Then call the Gillespie stochatis sim to see what happens. 

	    }
	}
	
	return 0;
}

