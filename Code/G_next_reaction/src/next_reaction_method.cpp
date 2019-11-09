#include "../include/next_reaction_method.h"
#include <iostream>
#include <cstddef>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <typeinfo> 

Next_reaction_method::Next_reaction_method(std::vector<Reaction*> r,std::map<char, int> init) {
	reactions = r ; 
	initial_values = init ; 
	initialize_plot_container() ; 
}

void Next_reaction_method::update_propensity(std::vector<double>& prop,int index,int ai) {
	prop[index] = ai ; 
}

void Next_reaction_method::simulate(RanGen& ran) {
	double t = 0 ;                          // set start time to 0 
	double t_end = 20 ;                    	// set end time 
	graph = new Dependency(reactions) ; 	// generate a dependency graph G 
	
	/* PHASE 1 */
	for (int i = 0; i < reactions.size(); i++) {
		// Calculate propensity function for all reactions
		a_i.push_back(reactions[i]->calculate_propensity(initial_values)) ;
		
		// For each reaction i -> generate a putative time tau_i with parameter a_i 
		double p_time = reactions[i]->calculate_putative_time(ran.randouble(), a_i[i], t) ; 
		
		// Store the p_times in the Priority queue 
		p_q.push(i, p_time) ; 
	}

	while (t < t_end) {
		/* PHASE 2 */
		/* The least putative time reaction */
		priority_queue::priority_queue_node<int, double> next = p_q.top() ; 
		int mu = next.key ; // mu 

		/* PHASE 3 */
		double prev_t = next.priority ;  

		Reaction* r = reactions[mu] ; 

		/* PHASE 4 
		 * Change the number of molecules to reflect the execution of reaction mu 
		 * Update t 
		*/
		std::vector<char> reactants = r->get_reactants() ; 
		std::vector<char> products = r->get_products() ; 
		
		for (const char &i : reactants) {
			initial_values[i]-- ; 
		}  
		for (const char &j : products) {
			initial_values[j]++ ;  
		}  

		/* PAHSE 5 
		 * For each edge (mu, alpha) in the dependency graph G, update data 
		 * of outgoing and incoming edges 
		*/
		// Update the current reaction  
		double next_estimate =std::numeric_limits<double>::infinity();
		if (a_i[mu] > 0.0) {
			a_i[mu] = r->calculate_propensity(initial_values) ; 
			next_estimate = r->calculate_putative_time(ran.randouble(), a_i[mu], prev_t) ; 
		}
		else {
			if(r->get_timeZero() <0.){ 
				r->set_lasta(a_i[mu]);
				r->set_timeZero(prev_t);
				r->set_last_putativeTime();
				a_i[mu]= 0.0;  // only now  allowed
			}
		}
		r->set_putativeTime(next_estimate) ; 
		p_q.update(mu, next_estimate) ;

		update_outgoing_edges(prev_t, mu, ran) ; 

		t += 1;  
		p_times.push_back(t) ; 
		fill_plot() ; 
	}
} 

void Next_reaction_method::update_outgoing_edges(double t, int mu, RanGen& ran) {
	std::vector<Edge*> edges = graph->get_edges() ; 

	for(size_t i = 0; i < edges.size(); i++){ 
		/* Each edge (mu, alpha)*/
		if (edges[i]->get_src()->get_id() == mu) {
			Reaction* r = edges[i]->get_dst() ; // the reaction alpha 
			int id_outgoing_edge = r->get_id() ; // the id of the reaction  
			
			if (id_outgoing_edge != mu) {
				double next_estimate =std::numeric_limits<double>::infinity();
				if (!a_i[id_outgoing_edge] > 0.0 && p_q.g_priority(id_outgoing_edge) < std::numeric_limits<double>::infinity() ) {
					if(r->get_timeZero() <0.){ 
						r->set_lasta(a_i[mu]);
						r->set_timeZero(t);
						r->set_last_putativeTime();
						a_i[mu]= 0.0;  // only now  allowed
					}
				}
				else if (a_i[id_outgoing_edge] > 0.0) {
					double prevtau = p_q.g_priority(id_outgoing_edge) ; 
					double t1 = t ; 
					double t2 = t ; 
					double a_old = a_i[id_outgoing_edge] ; 

					if (r->get_timeZero() >= 0.0) {
						a_old = r->get_lasta() ; 
						t1 = r->get_timeZero() ; 
						prevtau = r->get_last_putativeTime() ; 
						r->set_timeZero(-1.0) ; 
					}
					a_i[id_outgoing_edge] = r->calculate_propensity(initial_values) ;

					if (r->get_timeZero() < 0.0 && std::isinf(p_q.g_priority(id_outgoing_edge))){
						next_estimate = r->calculate_putative_time(ran.randouble(), a_i[id_outgoing_edge], t) ; 
					}
					else next_estimate = (a_old/a_i[id_outgoing_edge]*(prevtau-t1)+t2) ; 
					r->set_putativeTime(next_estimate) ; 
				}
				p_q.update(id_outgoing_edge, next_estimate) ;	 
			} 
			
		}
	}  
	/* Something quite not right with the tau updates ---> to see tonight */ 
}

void Next_reaction_method::display_tau(){

	/* Save results */
	std::ofstream sim;
	sim.open("./results/sim.txt");

	std::string t = "" ; 
	for (int i = 0 ; i < p_times.size() ; i++) {
		t += std::to_string(p_times[i]) ; 
		t += " " ;  
	}
	t += "\n" ;
	sim << t ;   

	std::map<char, std::vector<double>>::iterator it;
	for ( it = plots.begin(); it != plots.end(); it++ ){
		std::string temp = "" ; 
		temp += it->first ; 
		temp += " : " ; 
		for (int i = 0 ; i < it->second.size(); i++) {
			temp += std::to_string(plots[it->first][i]) ; 
			temp += " " ;  
		}
		temp += "\n" ;
		sim << temp ;  
	} 
	sim.close();

}

/* Keeps track of the number of molecules in the pool after appying a certain type of reaction*/
void Next_reaction_method::fill_plot() {
	std::map<char, std::vector<double>>::iterator it;
	for ( it = plots.begin(); it != plots.end(); it++ ){
		plots[it->first].push_back(initial_values[it->first]) ; 
	} 
}

void Next_reaction_method::initialize_plot_container(){
	std::map<char, int>::iterator it;
	for ( it = initial_values.begin(); it != initial_values.end(); it++ ){
		std::vector<double> tmp ; 
		tmp.push_back(it->second) ; 
		plots.insert(std::pair<char,std::vector<double>>(it->first, tmp)) ; 
	}
}