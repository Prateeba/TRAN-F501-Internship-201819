#include <utility>
#include <vector>
#include <ostream>
#include <iostream>


namespace Priority_queue{

	/* Encapsulate a priority queue node */
	template <typename Key, typename Priority> struct P_queue_node {
		Key key ;							// Reaction number 
		Priority priority ;					// putative time 
		P_queue_node(const Key& key, const Priority& priority) : key(key), priority(priority)  {}

		friend bool operator<(const P_queue_node& n1, const P_queue_node& n2) {
				return n1.priority < n2.priority;
		}

		friend bool operator>(const P_queue_node& n1, const P_queue_node& n2) {
				return n1.priority > n2.priority;
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

			/* Add an element to the heap*/
			void push(const Key& key, const Priority& priority) {int n = heap.size(); id[key] = n ; heap.emplace_back(key, priority) ; }
			
			/* Find the reaction which has the minimum putative time */
			const P_queue_node<Key, Priority>& top() {return heap.front() ;}
			
			/* Update an already existing element */
			void update(Key key, Priority new_priority) {
				int heap_index = id[key] ;   // the index at which the object is stored in the heap 
				Priority p = heap[heap_index].priority ; 

				if (new_priority > p) {
					heap[heap_index].priority = new_priority ; 
					sift_up(heap_index) ;
				}
				else {
					heap[heap_index].priority = new_priority ; 
					sift_down(heap_index) ; 
				}
			}

		private : 
			void sift_down(size_t heap_index) {
				size_t len = heap.size();
				size_t child = heap_index*2+1;
				if(len < 2 || child >= len) return;
				if(child+1 < len && heap[child+1] > heap[child]) ++child; // Check whether second child is higher
				if(!(heap[child] > heap[heap_index])) return; // Already in heap order

				P_queue_node<Key,Priority> val = std::move(heap[heap_index]);
				do {
					heap[heap_index] = std::move(heap[child]);
					id[heap[heap_index].key] = heap_index;
					heap_index = child;
					child = 2*child+1;
					if(child >= len) break;
					if(child+1 < len && heap[child+1] > heap[child]) ++child;
				} while(heap[child] > val);
				heap[heap_index] = std::move(val);
				id[heap[heap_index].key] = heap_index;
			}

			void sift_up(size_t heap_index) {
				size_t len = heap.size();
				if(len < 2 || heap_index <= 0) return;
				size_t parent = (heap_index-1)/2;
				if(!(heap[heap_index] > heap[parent])) return;
				P_queue_node<Key, Priority> val = std::move(heap[heap_index]);
				do {
					heap[heap_index] = std::move(heap[parent]);
					id[heap[heap_index].key] = heap_index;
					heap_index = parent;
					if(heap_index <= 0) break;
					parent = (parent-1)/2;
				} while(heap[heap_index] > heap[parent]);
				heap[heap_index] = std::move(val);
				id[heap[heap_index].key] = heap_index;
			}

	}; 
}