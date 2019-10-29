#ifndef DEF_MODEL
#define DEF_MODEL
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "../include/reaction.h"

class Model{

private :
	std::vector<Reaction*> reactions ; 
	std::map<char, int> initial_values ; 
	std::string name ; 

public : 
	Model(std::string name, std::vector<Reaction*> reactions, std::map<char, int> initial_values) : name(name), reactions(reactions), initial_values(initial_values) {} ; 
	std::vector<Reaction*> get_reactions() {return reactions ;}
	std::map<char, int> get_initial_values() {return initial_values ;}
	std::string get_name() {return name ; }
} ; 


#endif