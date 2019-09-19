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

	std::vector<double> p_times{0};  // for plotting -> time   
	std::map<char, std::vector<int>> plots {{'A', {10}},{'B', {10}} ,{'C', {10}} ,{'D', {10}}, {'E', {10}}, {'F', {10}}, {'G', {10}}}; // for plotting -> number of molecules 

public : 
	Next_reaction_method(std::vector<Reaction*>) ; 
	Priority_queue<int, double> get_p_q(){return p_q ; } 
	void simulate(std::map<char, int>, RanGen&) ; 
	void display_tau() ; 
	void display_number_of_molecules() ; 
	void fill_plot() ; 
} ; 











#endif