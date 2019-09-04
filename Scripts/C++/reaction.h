#ifndef DEF_REACTION
#define DEF_REACTION
#include <iostream>
#include <cstddef>
#include <string>
#include <vector>
#include <map>

class Node{	
	private : 
		char type ;  // type of molecule for e.g A,B,C,D,E etc 
	public : 
		Node(char t) {type = t;}  
		~Node() {}
		char getType() {return type ;}
		void setType(char t) {type = t;}
} ; 

class Reaction{

private : 
	std::vector<Node*> reactants;  // All reactions of the reaction 
	std::vector<Node*> products;   // All products of the reaction 
	int k;                         // reaction parameter

	
public : 
	Reaction(std::vector<char>, std::vector<char>, int) ; 
	~Reaction() ; 
	void display() ;
	void display_vector(std::vector<Node*>) ; 
	int calculate_propensity_function(std::map<char, int>) ; // a_i
	std::vector<Node*> depends_on() ;                        // Only the set of reactants 
	std::vector<Node*> affects() ;                           // 
} ;  


#endif 