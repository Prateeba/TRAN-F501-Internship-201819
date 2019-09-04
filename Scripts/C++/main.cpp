#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "reaction.h"


int main(){
	std::map<char, int> initial_values {{'A', 10},{'B', 10} ,{'C', 10} ,{'D', 10}, {'E', 10}, {'F', 10}};
	
	std::vector<char> r = {'A','B'} ; 
	std::vector<char> p = {'C'} ;
	Reaction* r1 = new Reaction(r,p,1) ; 
	r1->display() ; 
	r1->display_vector(r1->depends_on());
	r1->display_vector(r1->affects()) ;

	std::vector<char> r_1 = {'B','C'} ; 
	std::vector<char> p_1 = {'D'} ;
	Reaction* r2 = new Reaction(r_1,p_1,1) ; 
	r2->display() ; 
	r2->display_vector(r2->depends_on());
	r2->display_vector(r2->affects()) ;

	std::vector<char> r_2 = {'D','E'} ; 
	std::vector<char> p_2 = {'E','F'} ;
	Reaction* r3 = new Reaction(r_2,p_2,1) ; 
	r3->display() ; 
	r3->display_vector(r3->depends_on());
	r3->display_vector(r3->affects()) ;

	std::vector<char> r_3 = {'F'} ; 
	std::vector<char> p_3 = {'D','G'} ;
	Reaction* r4 = new Reaction(r_3,p_3,1) ; 
	r4->display() ; 
	r4->display_vector(r4->depends_on());
	r4->display_vector(r4->affects()) ;

	std::vector<char> r_4 = {'E','G'} ; 
	std::vector<char> p_4 = {'A'} ;
	Reaction* r5 = new Reaction(r_4,p_4,1) ; 
	r5->display() ; 
	r5->display_vector(r5->depends_on());
	r5->display_vector(r5->affects()) ;

	return 0 ; 
}