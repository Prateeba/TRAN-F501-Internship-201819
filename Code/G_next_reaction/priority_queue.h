#ifndef DEF_PRIORITY_QUEUE
#define DEF_PRIORITY_QUEUE
#include <iostream>
#include <cstddef>
#include <string>
#include <vector>
#include <map>
#include <queue>

class Heap_node{
private : 
	char id ;                   // the name of the heap_node 
	int reaction_number ;       // 
	double putative_time ;      // supposed reaction time 
	Heap_node* left ;           // left child 
	Heap_node* right ;          // right child 

public :
	Heap_node(char i, int num, double t){id = i; reaction_number = num ; putative_time = t ;} // Initialise a node object 
	~Heap_node() ; 
	char get_id(){return id ;}
	int get_reaction_number(){return reaction_number ;}
	double get_putative_time(){return putative_time ;}
	Heap_node* get_left() {return left ;}
	void set_left(Heap_node* l) {left = l ;}
	Heap_node* get_right() {return right ;}
	void set_right(Heap_node* r) {right = r ;}
} ; 

struct Comp{
    bool operator()(Heap_node* a, Heap_node* b){
        return a->get_putative_time() > b->get_putative_time();
    }
};

class Priority_queue{
private :
	//char[num_reactions] ;       // index structre -> not sure about this data structure yet 
	std::priority_queue<Heap_node*, std::vector<Heap_node*>, Comp> p_queue; 

public :
	Priority_queue(std::vector<Heap_node*>) ; // take as input all putative time converted into heap_nodes  + also has to initialise the index structure
	~Priority_queue() ; 
	Heap_node* get_min() ;  

} ; 



#endif 