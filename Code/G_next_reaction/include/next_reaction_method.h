#ifndef DEF_NEXT_REACTION_METHOD
#define DEF_NEXT_REACTION_METHOD
#include "reaction.h"
#include "dependency.h"

class Next_reaction_method {

private :  
	Dependency* graph ; 
	std::vector<double> a_i ;            // Keep track of the propensity of each reaction
	std::vector<double> p_times{0};   // for plotting -> time   
	std::vector<Reaction*> reactions ; 
	std::map<char, int> initial_values ; 
	priority_queue::updatable_priority_queue<int, double> p_q ; 
	std::map<char, std::vector<int>> plots {{'A', {10}},{'B', {10}} ,{'C', {10}} ,{'D', {10}}, {'E', {10}}, {'F', {10}}, {'G', {10}}}; // for plotting -> number of molecules 

public : 
	Next_reaction_method(std::vector<Reaction*>) ; 
	priority_queue::updatable_priority_queue<int, double>get_p_q(){return p_q ;} 
	void update_propensity(std::vector<double>&, int, int) ; 
	void simulate(std::map<char, int>, RanGen&) ; 
	void update_outgoing_edges(double, int, RanGen& ran) ; 
	void display_number_of_molecules() ; 
	void display_tau() ; 
	void fill_plot() ; 
} ; 











#endif