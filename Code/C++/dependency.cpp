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