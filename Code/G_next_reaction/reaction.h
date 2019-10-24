#ifndef DEF_REACTION
#define DEF_REACTION
#include <iostream>
#include <cstddef>
#include <string>
#include <vector>
#include <map>

class Reaction{

private : 
	std::vector<char> reactants;  // All reactions of the reaction 
	std::vector<char> products;   // All products of the reaction 
	int k;                        // reaction parameter
	int id ;                      // The reaction id in order to identify the reactions easily

	
public : 
	Reaction(std::vector<char>, std::vector<char>, int, int) ; 
	~Reaction() ; 
	void display() ; 
	void display_with_k() ;
	void display_vector(std::vector<char>) ; 
	int get_id() {return id ;}
	std::vector<char> get_reactants() {return reactants ;}
	std::vector<char> get_products() {return products ;}
	double calculate_propensity_function(std::map<char, int>) ; // a_i
	std::vector<char> depends_on() ;                        // Only the set of reactants 
	std::vector<char> affects() ;                           // 
} ;  


#endif 