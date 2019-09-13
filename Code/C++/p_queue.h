#include <utility>
#include <vector>
#include <ostream>
#include <iostream>
#include <algorithm> 


namespace Priority_queue{

	/* Encapsulate a priority queue node */
	template <typename Key, typename Priority> struct P_queue_node {
		Key key ;							// Reaction number 
		Priority priority ;					// putative time 
		P_queue_node(const Key& key, const Priority& priority) : key(key), priority(priority)  {}

		friend bool operator<(const P_queue_node& n1, const P_queue_node& n2) {
				return n1.priority > n2.priority;
		}

		friend bool operator>(const P_queue_node& n1, const P_queue_node& n2) {
				return n1.priority < n2.priority;
		}
		
	};

	template <typename Key, typename Priority> class P_queue{
		protected :
			std::vector<int> id ;                            // Index structure to say id[reaction number i.e 0,1,2] is stored at index x in the heap
			std::vector<P_queue_node<Key, Priority>> heap ;     // Heap structure storing all nodes 
		
		public :
			/* Priority  constructor*/
			P_queue(int r) {id.resize(r, 0) ;} 
			
			/*  */
			bool is_empty() {return heap.empty() ;}
			
			/* */
			int size() {return heap.size() ;}

			std::vector<int> get_id() {return id ;}

			std::vector<P_queue_node<Key, Priority>> get_heap() {return heap ;}

			/* Add an element to the heap*/
			void push(const Key& key, const Priority& priority) {int n = heap.size(); id[key-1] = n ; heap.emplace_back(key, priority) ;}
			
			/* Find the reaction which has the minimum putative time */
			const P_queue_node<Key, Priority>& top() { std::make_heap (heap.begin(),heap.end()); return heap.front() ;}
			
			/* Update an already existing element */
			void update(Key key, Priority new_priority) {
				int heap_index = id[key] ;   // the index at which the object is stored in the heap 
				Priority p = heap[heap_index].priority ; 
				heap[heap_index].priority = new_priority ; 

			}

			void display_index_structure() {
				for(size_t i = 0; i < id.size(); i++){
					std::cout << "Reaction |" << i << "| is stored at index |" << id[i] <<"| of the heap"<< std::endl ; 					
				}
			}

			void display_heap(){
				for(size_t i = 0; i < heap.size(); i++){
					std::cout << "At index |" << i << "| Reaction num : |" << heap[i].key << "| putative time " << heap[i].priority << std::endl ;   
				}
			}

		private : 

	}; 
}