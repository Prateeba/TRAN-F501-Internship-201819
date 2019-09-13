#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "reaction.h"
#include "dependency.h"



int main(){

	std::map<char, int> initial_values {{'A', 10},{'B', 10} ,{'C', 10} ,{'D', 10}, {'E', 10}, {'F', 10}};
	std::vector<Reaction*> reactions ; 

	std::vector<char> r = {'A','B'} ; 
	std::vector<char> p = {'C'} ;
	Reaction* r1 = new Reaction(r,p,1, 0) ; 

	std::vector<char> r_1 = {'B','C'} ; 
	std::vector<char> p_1 = {'D'} ;
	Reaction* r2 = new Reaction(r_1,p_1,1, 1) ; 

	std::vector<char> r_2 = {'D','E'} ; 
	std::vector<char> p_2 = {'E','F'} ;
	Reaction* r3 = new Reaction(r_2,p_2,1, 2) ; 

	std::vector<char> r_3 = {'F'} ; 
	std::vector<char> p_3 = {'D','G'} ;
	Reaction* r4 = new Reaction(r_3,p_3,1, 3) ; 

	std::vector<char> r_4 = {'E','G'} ; 
	std::vector<char> p_4 = {'A'} ;
	Reaction* r5 = new Reaction(r_4,p_4,1, 4) ; 

	reactions.push_back(r1) ;
	reactions.push_back(r2) ;
	reactions.push_back(r3) ;
	reactions.push_back(r4) ;
	reactions.push_back(r5) ;     

	Dependency* graph = new Dependency(reactions) ; 
	Priority_queue::P_queue<int, double> p_q(5) ; 
	p_q.push(0, 11.3) ; 
	p_q.push(1, 2.8) ; 
	p_q.push(2, 3.4) ; 
	p_q.push(3, 2.4) ; 
	p_q.push(4, 2.04) ; 

	RanGen ran;
	
	p_q.display_index_structure() ; 
	p_q.display_heap() ; 

	Priority_queue::P_queue_node<int, double> res = p_q.top() ; 
	std::cout <<"Reaction number : " << res.key << " | Least putative time : " << res.priority <<  std::endl ; 

	/*graph->update_outgoing_edges(1, 5, initial_values, p_q, ran) ; 
	Priority_queue::P_queue_node<int, double> res = p_q.top() ; 
	std::cout <<"Reaction number : " << res.key << " | Least putative time : " << res.priority <<  std::endl ; */

	/* std::cout << "Updating reaction 5's putative time ..." << std::endl ; 
	p_q.update(5, 5.9) ;  
	Priority_queue::P_queue_node<int, double> res_update = p_q.top() ; 
	std::cout <<"Reaction number : " << res_update.key << " | Least putative time : " << res_update.priority <<  std::endl ; */

	return 0 ; 
}