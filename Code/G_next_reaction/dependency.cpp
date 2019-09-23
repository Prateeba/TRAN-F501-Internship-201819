#include "dependency.h"
#include <iostream>
#include <cstddef>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

void Dependency::create_graph() {
	/* Loop through the list of reactions -> well double loop 
	*  If Affects(ri) intersects DependsOn(rj) != empty
	*/ 
	for(size_t i = 0; i < reactions.size(); i++){
		for(size_t j = 0; j < reactions.size(); j++){
			std::vector<char> affects = reactions[i]->affects(); 
			std::vector<char> depends = reactions[j]->depends_on();
			std::vector<char> temp ; 
			std::set_intersection(affects.begin(), affects.end(), depends.begin(), depends.end(),std::back_inserter(temp));
			if (temp.size()> 0) {
				add_edge_to_graph(reactions[i], reactions[j]) ;
			}
		}
	}
}

void Dependency::add_edge_to_graph(Reaction* src, Reaction* dst) {
	Edge* e = new Edge(src, dst) ; 
	edges.push_back(e) ; 
}

void Dependency::delete_edge(Reaction* src, Reaction* dst) {
	// loop through edges list
	// If we find the edge with the given src and dst -> remove from edges list 

}
void Dependency::display_graph() {
	// loop through the list of edges and print them off .. 
	for(size_t i = 0; i < edges.size(); i++){
		edges[i]->get_src()->display() ; 
		std::cout << "\033[1;31m======>>\033[0m\n";
		edges[i]->get_dst()->display() ; 
	}
}

void Dependency::update_outgoing_edges(int t, int mu, std::map<char, int> initial_values, Priority_queue<int, double>& p_q, RanGen& ran) {
	for(size_t i = 0; i < edges.size(); i++){
		if (edges[i]->get_src()->get_id() == mu) {
			Reaction* r = edges[i]->get_dst() ; 
			int a_new = r->calculate_propensity_function(initial_values) ; 
			// TO DO -> update a_alpha which is not done 
			
			int id_outgoing_edge = r->get_id() ; 
			double t_alpha = std::numeric_limits<double>::infinity(); 
			
			if (id_outgoing_edge != mu) {
				double a_old = p_q.get_priority(id_outgoing_edge) ; 
				t_alpha  = (a_old/a_new)*(t_alpha - t) + t ;   
			} 

			else if (id_outgoing_edge == mu ) {
				double random_number = ran.randouble() ; 
				t_alpha = random_number + t ;
			}
			p_q.update(id_outgoing_edge, t_alpha) ; 
		}
	}
}