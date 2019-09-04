#include "reaction.h"
#include <iostream>
#include <cstddef>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>


Reaction::Reaction(std::vector<char> r, std::vector<char> p, int react_param) {
	for(size_t i = 0; i < r.size(); i++){
		Node * temp = new Node(r[i]) ;
		reactants.push_back(temp) ; 
	}
	for(size_t i = 0; i < p.size(); i++){
		Node * temp = new Node(p[i]) ;
		products.push_back(temp) ; 
	}  
	k = react_param ; 
}

void Reaction::display(){ 
	for(size_t i = 0; i < reactants.size()-1; i++){
		std::cout << reactants[i]->getType() << " + ";
	}
	std::cout << reactants[reactants.size()-1]->getType() << " --(" << k << ")--> " ; 
	for(size_t i = 0; i < products.size()-1; i++){
		std::cout << products[i]->getType() << " + ";
	}
	std::cout << products[products.size()-1]->getType() << std::endl ; 
}

void Reaction::display_vector(std::vector<Node*> v) {
	std::cout << "{" ; 
	for(size_t i = 0; i < v.size()-1; i++){
		std::cout << v[i]->getType() << ",";
	}
	std::cout << v[v.size()-1]->getType() << "}" << std::endl ; 
}

int Reaction::calculate_propensity_function(std::map<char, int> initial_values){
	/* Doing some funny things */
	int sum = k ; 
	for(size_t i = 0; i < reactants.size(); i++){
		sum = sum * initial_values[reactants[i]->getType()] ; 
	}
	return sum ; 
}

std::vector<Node*> Reaction::depends_on() {
	/* Reactant(mu) = DependsOn(mu)*/
	return reactants ; 
}

std::vector<Node*> Reaction::affects() {
	/* Affects(mu) = Reactants(mu) U Products(mu) except when catalytic reactions */
	std::vector<Node*> temp_r = reactants ; 
	std::vector<Node*> temp_p = products ;

	for(size_t i = 0; i < temp_r.size(); i++){
		for(size_t j = 0; j < temp_p.size(); j++){
			if (temp_r[i]->getType() == temp_p[j]->getType()) {
				temp_r.erase(std::remove(temp_r.begin(), temp_r.end(), temp_r[i]), temp_r.end());
				temp_p.erase(std::remove(temp_p.begin(), temp_p.end(), temp_p[j]), temp_p.end());
			}
		}
	}
	std::vector<Node*> result;
	std::set_union(temp_r.begin(), temp_r.end(), temp_p.begin(), temp_p.end(), std::back_inserter(result)); 
	return result ; 
}

