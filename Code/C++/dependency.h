#ifndef DEF_DEPENDENCY
#define DEF_DEPENDENCY
#include <iostream>
#include "reaction.h"
#include <cstddef>
#include <string>
#include <vector>
#include <map>

class Edge{
private :
	Reaction* src ; 
	Reaction* dst ;  

public :  
	Edge(Reaction* s, Reaction* d) {src = s ; dst = d;}
	~Edge() {}
	Reaction* get_src() {return src;}
	Reaction* get_dst() {return dst;}
} ; 

class Dependency{ 
	/* Take a list of reactions (which will then represent the nodes of the graph)
     * Connect each reaction/node according to the rule defined in the paper 
	*/ 

private : 
	std::vector<Reaction*> reactions;    // The set of nodes
	std::vector<Edge*> edges;            // The set of edges 
public : 
	Dependency(std::vector<Reaction*> r) {reactions = r; create_graph();}
	~Dependency() {}
	void create_graph() ; 
	void add_edge_to_graph(Reaction*, Reaction*) ;  
	void delete_edge(Reaction*, Reaction*) ; 
	void display_graph() ; 
} ; 


#endif 