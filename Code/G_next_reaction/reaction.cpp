#include "reaction.h"
#include <iostream>
#include <cstddef>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>


Reaction::Reaction(std::vector<char> r, std::vector<char> p, int react_param, int i) {
	reactants = r ; 
	products = p ; 
	k = react_param ; 
	id = i ; 
}
void Reaction::display(){ 
	for(size_t i = 0; i < reactants.size()-1; i++){
		std::cout << reactants[i] << " + ";
	}
	std::cout << reactants[reactants.size()-1] << " ---> " ; 
	for(size_t i = 0; i < products.size()-1; i++){
		std::cout << products[i] << " + ";
	}
	std::cout << products[products.size()-1] << std::endl ; 
}

void Reaction::display_with_k(){ 
	for(size_t i = 0; i < reactants.size()-1; i++){
		std::cout << reactants[i] << " + ";
	}
	std::cout << reactants[reactants.size()-1] << " --(" << k << ")--> " ; 
	for(size_t i = 0; i < products.size()-1; i++){
		std::cout << products[i] << " + ";
	}
	std::cout << products[products.size()-1] << std::endl ; 
}

void Reaction::display_vector(std::vector<char> v) {
	std::cout << "{" ; 
	for(size_t i = 0; i < v.size()-1; i++){
		std::cout << v[i] << ",";
	}
	std::cout << v[v.size()-1] << "}" << std::endl ; 
}

double Reaction::calculate_propensity_function(std::map<char, int> initial_values){
	/* Doing some funny things */
	int sum = k ; 
	for(size_t i = 0; i < reactants.size(); i++){
		sum = sum * initial_values[reactants[i]] ; 
	}
	return sum ; 
}

std::vector<char> Reaction::depends_on() {
	/* Reactant(mu) = DependsOn(mu)*/
	return reactants ; 
}

std::vector<char> Reaction::affects() {
	/* Affects(mu) = Reactants(mu) U Products(mu) except when catalytic reactions */
	std::vector<char> temp_r = reactants ; 
	std::vector<char> temp_p = products ;

	for(size_t i = 0; i < temp_r.size(); i++){
		for(size_t j = 0; j < temp_p.size(); j++){
			if (temp_r[i] == temp_p[j]) {
				temp_r.erase(std::remove(temp_r.begin(), temp_r.end(), temp_r[i]), temp_r.end());
				temp_p.erase(std::remove(temp_p.begin(), temp_p.end(), temp_p[j]), temp_p.end());
			}
		}
	}
	std::vector<char> result;
	std::set_union(temp_r.begin(), temp_r.end(), temp_p.begin(), temp_p.end(), std::back_inserter(result)); 
	return result ; 
}

