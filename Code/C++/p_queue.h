#include <utility>
#include <vector>
#include <ostream>
#include <iostream>
#include <algorithm> 

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
			std::vector<size_t> id_to_heappos;                   // Index structure that keeps track of each node in the heap 
			std::vector<Priority_queue_node<Key,Priority>> heap; // Heap structure where top element is the reaction that has the least putative time 
		public:
			/* Constructor */
			Priority_queue() {}

			/* */
			bool empty()       const { return heap.empty(); }
			
			/* */
			std::size_t size() const { return heap.size(); }

			/* */
			std::vector<size_t> get_id_to_heappos() const {return id_to_heappos ;}

			std::vector<Priority_queue_node<Key,Priority>> get_heap() const {return heap ;}
			
			/* Get the reaction with the least putative time  */
			const Priority_queue_node<Key,Priority>& top() const { return heap.front(); }
			
			/* Remove the least putative time reaction */
			Priority_queue_node<Key,Priority> pop_value(bool remember_key=true) {
				if(size() == 0) return Priority_queue_node<Key, Priority>(-1, Priority());
				Priority_queue_node<Key,Priority> ret = std::move(*heap.begin());
				id_to_heappos[ret.key] = -1-remember_key;
				if(size() > 1)
					*heap.begin() = std::move(*(heap.end()-1));
				heap.pop_back();
				sift_down(0);
				return ret;
			}
			
			/* Return the priority of a given key */
			Priority get_priority(const Key& key) {
				if(key >= id_to_heappos.size()) {
					size_t pos = id_to_heappos[key];
					if(pos >= 0) {
						return heap[pos].priority ;
					}
				}
				return 0;
			}
			
			/* Return true if a node has been added successfully  and it doen't push a duplicate node */
			bool push(const Key& key, const Priority& priority) {
				extend_ids(key);
				if(id_to_heappos[key] < ((size_t)-2)) {
					return false;
				}
				
				// otherwise we have id_to_heappos[key] = -1, unseen key
				size_t n = heap.size();
				id_to_heappos[key] = n; // For consistency in the case where nothing moves (early return)
				heap.emplace_back(key,priority);
				sift_up(n);
				return true;
			}

			/** Returns true if the key was already inside and was updated, otherwise does nothing and returns false */
			bool update(const Key& key, const Priority& new_priority, bool only_if_higher=false) {
				if(key >= id_to_heappos.size()) return false;
				size_t heappos = id_to_heappos[key];
				if(heappos >= ((size_t)-2)) return false;
				Priority& priority = heap[heappos].priority;
				if(new_priority > priority) {
					priority = new_priority;
					sift_up(heappos);
					return true;
				}
				else if(!only_if_higher && new_priority < priority) {
					priority = new_priority;
					sift_down(heappos);
					return true;
				}
				return false;
			}
		private:
			void extend_ids(Key k) {
				size_t new_size = k+1;
				if(id_to_heappos.size() < new_size)
					id_to_heappos.resize(new_size, -1);
			}
			void sift_down(size_t heappos) {
				size_t len = heap.size();
				size_t child = heappos*2+1;
				if(len < 2 || child >= len) return;
				if(child+1 < len && heap[child+1] > heap[child]) ++child; // Check whether second child is higher
				if(!(heap[child] > heap[heappos])) return; // Already in heap order
				Priority_queue_node<Key,Priority> val = std::move(heap[heappos]);
				do {
					heap[heappos] = std::move(heap[child]);
					id_to_heappos[heap[heappos].key] = heappos;
					heappos = child;
					child = 2*child+1;
					if(child >= len) break;
					if(child+1 < len && heap[child+1] > heap[child]) ++child;
				} while(heap[child] > val);
				heap[heappos] = std::move(val);
				id_to_heappos[heap[heappos].key] = heappos;
			}
			void sift_up(size_t heappos) {
				size_t len = heap.size();
				if(len < 2 || heappos <= 0) return;
				size_t parent = (heappos-1)/2;
				if(!(heap[heappos] > heap[parent])) return;
				Priority_queue_node<Key, Priority> val = std::move(heap[heappos]);
				do {
					heap[heappos] = std::move(heap[parent]);
					id_to_heappos[heap[heappos].key] = heappos;
					heappos = parent;
					if(heappos <= 0) break;
					parent = (parent-1)/2;
				} while(heap[heappos] > heap[parent]);
				heap[heappos] = std::move(val);
				id_to_heappos[heap[heappos].key] = heappos;
			}
	};
