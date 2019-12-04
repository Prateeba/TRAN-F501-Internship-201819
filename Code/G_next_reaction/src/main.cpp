#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "../include/model.h"
#include "../include/models.h"
#include "../include/rangen.h"
#include "../include/reaction.h"
#include "../include/next_reaction_method.h"


int main(){

	//Models m; Model r = m.nucleation_elongation(9.99e+11)  ; 
	//Models m ; Model r = m.random() ; 
	Models m; Model r = m.secondary_nucleation(2.2449157107307083, 0.4569655450)  ; 
	RanGen ran; 

	Next_reaction_method* n = new Next_reaction_method(r.get_reactions(), r.get_initial_values()) ; 	
	n->simulate(ran) ; 
	n->display_tau() ; 

	/* plot raw data */
	std::string filename = "src/plot.py";
	std::string command = "python ";
	command += filename;
	system(command.c_str()); 
	
	return 0 ; 
}