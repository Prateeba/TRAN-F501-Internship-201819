#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "reaction.h"
#include "dependency.h"
//#include "priority_queue.h"
#include "p_queue.h"


int main(){

	std::map<char, int> initial_values {{'A', 10},{'B', 10} ,{'C', 10} ,{'D', 10}, {'E', 10}, {'F', 10}};
	std::vector<Reaction*> reactions ; 

	std::vector<char> r = {'A','B'} ; 
	std::vector<char> p = {'C'} ;
	Reaction* r1 = new Reaction(r,p,1) ; 

	std::vector<char> r_1 = {'B','C'} ; 
	std::vector<char> p_1 = {'D'} ;
	Reaction* r2 = new Reaction(r_1,p_1,1) ; 

	std::vector<char> r_2 = {'D','E'} ; 
	std::vector<char> p_2 = {'E','F'} ;
	Reaction* r3 = new Reaction(r_2,p_2,1) ; 

	std::vector<char> r_3 = {'F'} ; 
	std::vector<char> p_3 = {'D','G'} ;
	Reaction* r4 = new Reaction(r_3,p_3,1) ; 

	std::vector<char> r_4 = {'E','G'} ; 
	std::vector<char> p_4 = {'A'} ;
	Reaction* r5 = new Reaction(r_4,p_4,1) ; 

	reactions.push_back(r1) ;
	reactions.push_back(r2) ;
	reactions.push_back(r3) ;
	reactions.push_back(r4) ;
	reactions.push_back(r5) ;     

	Dependency* graph = new Dependency(reactions) ; 
	graph->display_graph() ;  

	/*std::vector<Heap_node*> heap_nodes ; 
	Heap_node* n = new Heap_node('A', 8, 1.3) ; 
	Heap_node* n1 = new Heap_node('B', 1, 4.2) ;
	Heap_node* n2 = new Heap_node('C', 6, 2.0) ;
	Heap_node* n3 = new Heap_node('D', 9, 7.3) ;
	Heap_node* n4 = new Heap_node('E', 4, 5.5) ;
	heap_nodes.push_back(n) ;
	heap_nodes.push_back(n1) ;
	heap_nodes.push_back(n2) ; 
	heap_nodes.push_back(n3) ; 
	heap_nodes.push_back(n4) ; 

	Priority_queue* pq = new Priority_queue(heap_nodes) ; */

	Priority_queue::P_queue<int, double> p_q(5) ; 
	p_q.push(5, 1.4) ; 
	p_q.push(1, 2.8) ; 
	p_q.push(2, 3.4) ; 
	p_q.push(3, 2.4) ; 

	Priority_queue::P_queue_node<int, double> res = p_q.top() ; 
	std::cout <<"Reaction number : " << res.key << " | Least putative time : " << res.priority <<  std::endl ; 

	std::cout << "Updating reaction 5's putative time ..." << std::endl ; 
	p_q.update(5, 5.9) ;  
	Priority_queue::P_queue_node<int, double> res_update = p_q.top() ; 
	std::cout <<"Reaction number : " << res_update.key << " | Least putative time : " << res_update.priority <<  std::endl ; 

	return 0 ; 
}