#include "priority_queue.h"


int main(){
	Priority_queue<int,double> pq ; 
	Priority_queue_node n(33, 2.03) ; 
	Priority_queue_node n1(2, 20.3) ;
	Priority_queue_node n2(3, 290.3) ;
	Priority_queue_node n3(87, 0.00003) ;
	
	pq.push(n2);
	pq.push(n) ; 
	pq.push(n1);  
	pq.push(n3);  

	pq.get_least_tau() ; 

}