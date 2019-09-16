#include "next_reaction_method.h"
#include <iostream>
#include <cstddef>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

Next_reaction_method::Next_reaction_method(std::vector<Reaction*> r) {
	reactions = r ; 
}

void Next_reaction_method::simulate(std::map<char, int> values, RanGen& ran) {
	initial_values = values ;           // set initial numbers of molecules 
	t = 0 ;                             // set start time to 0 
	int t_end = 5 ;                    // set end time 
	graph = new Dependency(reactions) ; // generate a dependency graph 

	/* PHASE 1 */
	for (int i = 0; i < reactions.size(); i++) {
		// Calculate propensity function for all reactions
		reactions[i]->calculate_propensity_function(initial_values) ;
		// For each reaction i -> generate a putative time tau_i 
		double p_time = ran.randouble() ; // TO CHANGE -> SOME MISUNDERSTANDING OVER HERE 
		// Store the p_times in the Priority queue 
		p_q.push(i+1, p_time) ; 
	}

	while (t < t_end) {
		/* PHASE 2 
		 * least putative time reaction 
		*/
		Priority_queue_node<int, double> res = p_q.top() ; 
		int mu = res.key ; 

		/* PHASE 3 */
		double tau = res.priority ; 

		/* PHASE 4 
		 * Change the number of molecules to reflect the execution of reaction mu 
		 * Update t 
		*/
		Reaction* r = reactions[mu] ; 
		std::vector<char> reactants = r->get_reactants() ; 
		std::vector<char> products = r->get_products() ; 
		for (int i = 0; i < reactants.size(); i++) {
			initial_values[reactants[i]]-- ; 
			plots[reactants[i]].push_back(initial_values[reactants[i]]) ; 
		}  
		for (int i = 0; i < products.size(); i++) {
			initial_values[products[i]]++ ; 
			plots[products[i]].push_back(initial_values[products[i]]) ; 
		}  
		t += tau ; 
		p_times.push_back(t) ; 

		/* PAHSE 5 
		 * For each edge (mu, alpha) in the dependency graph G, update data 
		 * of outgoing and incoming edges 
		*/
		graph->update_outgoing_edges(1, mu, initial_values, p_q, ran) ; 
		p_q.display_heap() ; 

		Priority_queue_node<int, double> res_final = p_q.top() ; 
	}
} 

void Next_reaction_method::display_tau(){
	std::cout << p_times.size() ;
	/*for (int i = 0; i < p_times.size();  i++){
		std::cout << p_times[i] << " A " << plots['A'][i] << std::endl ; 
		std::cout << p_times[i] << " B " << plots['B'][i] << std::endl ; 
		std::cout << p_times[i] << " C " << plots['C'][i] << std::endl ; 
		std::cout << p_times[i] << " D " << plots['D'][i] << std::endl ; 
		std::cout << p_times[i] << " E " << plots['E'][i] << std::endl ; 
		std::cout << p_times[i] << " F " << plots['F'][i] << std::endl ; 
		std::cout << p_times[i] << " G " << plots['G'][i] << std::endl ; 

	}*/
}