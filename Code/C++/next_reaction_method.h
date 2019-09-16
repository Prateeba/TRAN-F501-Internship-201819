#ifndef DEF_NEXT_REACTION_METHOD
#define DEF_NEXT_REACTION_METHOD
#include "reaction.h"
#include "dependency.h"

class Next_reaction_method {

private : 
	std::vector<Reaction*> reactions ; 
	Dependency* graph ; 
	Priority_queue<int, double> p_q ; 
	int t ; 
	std::map<char, int> initial_values ; 

	std::vector<double> p_times ;  // for plotting -> time   
	std::map<char, std::vector<int>> plots {{'A', {}},{'B', {}} ,{'C', {}} ,{'D', {}}, {'E', {}}, {'F', {}}, {'G', {}}}; // for plotting -> number of molecules 

public : 
	Next_reaction_method(std::vector<Reaction*>) ; 
	Priority_queue<int, double> get_p_q(){return p_q ; } 
	void simulate(std::map<char, int>, RanGen&) ; 
	void display_tau() ; 
	void display_number_of_molecules() ; 
} ; 











#endif