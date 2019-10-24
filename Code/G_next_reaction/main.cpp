#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "reaction.h"
#include "dependency.h"
#include "next_reaction_method.h" 


int main(){

	std::map<char, int> initial_values {{'A', 10},{'B', 10} ,{'C', 10} ,{'D', 10}, {'E', 10}, {'F', 10}, {'G', 10}};
	std::vector<Reaction*> reactions ; 

	std::vector<char> r = {'A','B'} ; 
	std::vector<char> p = {'C'} ;
	Reaction* r1 = new Reaction(r,p,1, 1) ; 
	 
	std::vector<char> r_1 = {'B','C'} ; 
	std::vector<char> p_1 = {'D'} ;
	Reaction* r2 = new Reaction(r_1,p_1,1, 2) ; 
	 
	std::vector<char> r_2 = {'D','E'} ; 
	std::vector<char> p_2 = {'E','F'} ;
	Reaction* r3 = new Reaction(r_2,p_2,1, 3) ; 
	 
	std::vector<char> r_3 = {'F'} ; 
	std::vector<char> p_3 = {'D','G'} ;
	Reaction* r4 = new Reaction(r_3,p_3,1, 4) ; 
	 
	std::vector<char> r_4 = {'E','G'} ; 
	std::vector<char> p_4 = {'A'} ;
	Reaction* r5 = new Reaction(r_4,p_4,1, 5) ; 
	 

	reactions.push_back(r1) ;
	reactions.push_back(r2) ;
	reactions.push_back(r3) ;
	reactions.push_back(r4) ;
	reactions.push_back(r5) ;     

	RanGen ran; 

	Next_reaction_method* n = new Next_reaction_method(reactions) ; 	
	n->simulate(initial_values, ran) ; 
	//n->display_tau() ; 
	
	return 0 ; 
}