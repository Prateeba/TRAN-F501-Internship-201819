#include "priority_queue.h"
#include <iostream>
#include <cstddef>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>
#include <queue>


Priority_queue::Priority_queue(std::vector<Heap_node*> nodes) {
	for(size_t i = 0; i < nodes.size(); i++){
		p_queue.push(nodes[i]) ; 
	}
	Heap_node* test = p_queue.top() ; 
	std::cout << test->get_id() << std::endl ; 
}

Heap_node* Priority_queue::get_min(){
	return p_queue.top() ; 
}