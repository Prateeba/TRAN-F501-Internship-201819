#include "next_reaction_method.h"
#include <iostream>
#include <cstddef>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <typeinfo> 

Next_reaction_method::Next_reaction_method(std::vector<Reaction*> r) {
	reactions = r ; 
}

void Next_reaction_method::simulate(std::map<char, int> values, RanGen& ran) {
	initial_values = values ;           // set initial numbers of molecules 
	t = 0 ;                             // set start time to 0 
	int t_end = 10 ;                    // set end time 
	graph = new Dependency(reactions) ; // generate a dependency graph 
	std::vector<int> a_i ; 

	/* PHASE 1 */
	for (int i = 0; i < reactions.size(); i++) {
		// Calculate propensity function for all reactions
		a_i.push_back(reactions[i]->calculate_propensity_function(initial_values)) ;
		// For each reaction i -> generate a putative time tau_i with parameter a_i 
		std::cout << "a_i" << a_i[i] << std::endl ; 
		double p_time = ran.ranexp(a_i[i]) ; 
		std::cout << "putative time " << p_time << std::endl ; 
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
		std::cout << "least putative time " << tau << std::endl ; 

		/* PHASE 4 
		 * Change the number of molecules to reflect the execution of reaction mu 
		 * Update t 
		*/
		Reaction* r = reactions[mu] ; 
		std::vector<char> reactants = r->get_reactants() ; 
		std::vector<char> products = r->get_products() ; 
		
		for (const char &i : reactants) {
			initial_values[i]-- ; 
		}  
		for (const char &j : products) {
			initial_values[j]++ ;  
		}  
		t += tau ; 
		p_times.push_back(t) ; 
		fill_plot() ; 

		/* PAHSE 5 
		 * For each edge (mu, alpha) in the dependency graph G, update data 
		 * of outgoing and incoming edges 
		*/
		graph->update_outgoing_edges(1, mu, initial_values, p_q, ran) ; 
	}
} 

void Next_reaction_method::display_tau(){
	/*for (int i = 0; i < p_times.size();  i++){
		printf("%f\t",p_times[i]);
		printf("%f\t",plots['A'][i]);
		printf("%f\t",plots['B'][i]);
	}*/

	for (int i = 0 ; i < p_times.size() ; i++) {
 		std::cout << p_times[i] << " " ; 
	}
	std::cout << "\n" ; 
	for (int i = 0 ; i < p_times.size() ; i++) {
 		std::cout << plots['A'][i] << " " ; 
	}
	std::cout << "\n" ; 
	for (int i = 0 ; i < p_times.size() ; i++) {
 		std::cout << plots['B'][i] << " " ; 
	}
	std::cout << "\n" ; 
	for (int i = 0 ; i < p_times.size() ; i++) {
 		std::cout << plots['C'][i] << " " ; 
	}
	std::cout << "\n" ; 
	for (int i = 0 ; i < p_times.size() ; i++) {
 		std::cout << plots['D'][i] << " " ; 
	}
	std::cout << "\n" ; 
	for (int i = 0 ; i < p_times.size() ; i++) {
 		std::cout << plots['E'][i] << " " ; 
	}
	std::cout << "\n" ; 
	for (int i = 0 ; i < p_times.size() ; i++) {
 		std::cout << plots['F'][i] << " " ; 
	}
	std::cout << "\n" ; 
	for (int i = 0 ; i < p_times.size() ; i++) {
 		std::cout << plots['G'][i] << " " ; 
	}


}

/* Keeps track of the number of molecules in the pool after appying a certain type of reaction*/
void Next_reaction_method::fill_plot() {
	plots['A'].push_back(initial_values['A']) ;  
	plots['B'].push_back(initial_values['B']) ; 
	plots['C'].push_back(initial_values['C']) ; 
	plots['D'].push_back(initial_values['D']) ; 
	plots['E'].push_back(initial_values['E']) ; 
	plots['F'].push_back(initial_values['F']) ; 
	plots['G'].push_back(initial_values['G']) ; 
}