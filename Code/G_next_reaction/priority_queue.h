#include <utility>
#include <vector>
#include <ostream>
#include <iostream>
#include <algorithm> 
#include <boost/heap/priority_queue.hpp>

using namespace boost::heap;


template <typename Key, typename Priority> struct Priority_queue_node {
	Priority priority;            // putative time 
	Key key;                      // Reaction's number 
	
	Priority_queue_node(const Key& key, const Priority& priority) : priority(priority), key(key) {}
	
	friend bool operator<(const Priority_queue_node& pqn1, const Priority_queue_node& pqn2) {
		return pqn1.priority > pqn2.priority;
	}
	friend bool operator>(const Priority_queue_node& pqn1, const Priority_queue_node& pqn2) {
		return pqn1.priority < pqn2.priority;
	}
};


template <typename Key, typename Priority> class Priority_queue {

protected:
	std::vector<size_t> id_to_heappos;                      // Index structure that keeps track of each node in the heap 
	priority_queue<Priority_queue_node<Key,Priority>> heap; // Heap structure where top element is the reaction that has the least putative time 

public:
	/* Constructor */
	Priority_queue() {}
	
	void push(Priority_queue_node<Key,Priority> n) { 
		std::cout << "Priority " << n.priority << std::endl ; 
		std::cout << "Key/id " << n.key << std::endl ;
		heap.push(n);
	}

	void /*Priority_queue_node<Key,Priority> */ get_least_tau() {
		std::cout << "Least or not Least : This is the question " << heap.top().key << std::endl ; 
	}


};


