#ifndef DEF_REACTION
#define DEF_REACTION
#include <iostream>
#include <cstddef>
#include <string>
#include <vector>
#include <cmath>
#include <map>

class Reaction{

private : 
	std::vector<char> reactants;  // All reactions of the reaction 
	std::vector<char> products;   // All products of the reaction 
	int k;                        // reaction parameter
	int id ;                      // The reaction id in order to identify the reactions easily
	double putativeTime ;         // Putative time of each reaction 

	double lasta ;                // to update outgoing edges 
	double last_putativeTime ;    // to update outgoing edges 
	double time_zero ;            // to update outgoing edges 

	
public : 
	Reaction(std::vector<char>, std::vector<char>, int, int) ; 
	~Reaction() ; 
	void display() ; 
	void display_with_k() ;
	void display_vector(std::vector<char>) ; 
	int get_id() {return id ;}
	double get_putative_time() {return putativeTime ; }
	void set_putativeTime(double t) {putativeTime = t ;}
	double calculate_putative_time(double ranval, double _a, double prev=0.0) {putativeTime = prev + (1.0 / _a ) * log(1.0/ranval); return putativeTime ; }
	std::vector<char> get_reactants() {return reactants ;}
	std::vector<char> get_products() {return products ;}
	double calculate_propensity(std::map<char, int>) ; 		// a_i
	std::vector<char> depends_on() ;                        // Only the set of reactants 
	std::vector<char> affects() ;                           // 

	void set_lasta(double a) {lasta = a ; }
	double get_lasta() {return lasta ;}
	void set_last_putativeTime() {last_putativeTime = putativeTime ; }
	double get_last_putativeTime() {return last_putativeTime ; }
	void set_timeZero(double t) {time_zero = t ;}
	double get_timeZero() {return time_zero ; }

} ;  


#endif 