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

	Models m; Model r = m.random() ; 
	RanGen ran; 

	Next_reaction_method* n = new Next_reaction_method(r.get_reactions()) ; 	
	n->simulate(r.get_initial_values(), ran) ; 
	n->display_tau() ; 
	
	return 0 ; 
}