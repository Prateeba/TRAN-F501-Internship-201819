#ifndef DEF_MODELS
#define DEF_MODELS
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "../include/reaction.h"
#include "../include/model.h"


class Models {
	/* All precharged models -> All models considered are unseeded models */
private : 


public : 
	Models() {}

	Model paper() {
		std::map<char, int> initial_values {{'W', 10},{'X', 10} ,{'Y', 10} ,{'Z', 10}};
		std::vector<Reaction*> reactions ;

		std::vector<char> r = {'X'} ; 
		std::vector<char> p = {'Y'} ;
		Reaction* r1 = new Reaction(r,p,1, 0) ; 

		std::vector<char> r_1 = {'Y'} ; 
		std::vector<char> p_1 = {'X'} ;
		Reaction* r2 = new Reaction(r_1,p_1,1, 1) ; 

		std::vector<char> r_2 = {'X', 'X'} ;  // P = 2X 
		std::vector<char> p_2 = {'Z'} ;
		Reaction* r3 = new Reaction(r_2,p_2,2, 2) ;

		std::vector<char> r_3 = {'Z'} ; 
		std::vector<char> p_3 = {'X', 'X'} ;
		Reaction* r4 = new Reaction(r_3,p_3,1, 3) ;

		std::vector<char> r_4 = {'W','X'} ; 
		std::vector<char> p_4 = {'X', 'X'} ;
		Reaction* r5 = new Reaction(r_4,p_4,2, 4) ;  

		std::vector<char> r_5 = {'X', 'X'} ; 
		std::vector<char> p_5 = {'W', 'X'} ;
		Reaction* r6 = new Reaction(r_5,p_5,1, 5) ;  

		reactions.push_back(r1) ;
		reactions.push_back(r2) ;
		reactions.push_back(r3) ;
		reactions.push_back(r4) ;
		reactions.push_back(r5) ;
		reactions.push_back(r6) ;

		return Model("Paper", reactions, initial_values) ; 
	}

	Model random() {
		std::map<char, int> initial_values {{'A', 6},{'B', 14} ,{'C', 8} ,{'D', 12}, {'E', 9}, {'F', 3}, {'G', 5}};
		std::vector<Reaction*> reactions ; 

		std::vector<char> r = {'A','B'} ; 
		std::vector<char> p = {'C'} ;
		Reaction* r1 = new Reaction(r,p,2, 0) ; 
		 
		std::vector<char> r_1 = {'B','C'} ; 
		std::vector<char> p_1 = {'D'} ;
		Reaction* r2 = new Reaction(r_1,p_1,1, 1) ; 
		 
		std::vector<char> r_2 = {'D','E'} ; 
		std::vector<char> p_2 = {'E','F'} ;
		Reaction* r3 = new Reaction(r_2,p_2,2, 2) ; 
		 
		std::vector<char> r_3 = {'F'} ; 
		std::vector<char> p_3 = {'D','G'} ;
		Reaction* r4 = new Reaction(r_3,p_3,2, 3) ; 
		 
		std::vector<char> r_4 = {'E','G'} ; 
		std::vector<char> p_4 = {'A'} ;
		Reaction* r5 = new Reaction(r_4,p_4,1, 4) ; 

		reactions.push_back(r1) ;
		reactions.push_back(r2) ;
		reactions.push_back(r3) ;
		reactions.push_back(r4) ;
		reactions.push_back(r5) ;    

		return Model("Random", reactions, initial_values) ;   
	}

	Model nucleation_elongation(int kn_kplus) {
		/* Here we have two reactions :  
		 * 1. Monomers -> Formation of primary nuclei 
		 * 2. Monomers -> Add themselves to Fibril ends 
		 */ 
		std::map<char, int> initial_values {{'M', 10000},{'P', 4000} ,{'F', 3000}};
		std::vector<Reaction*> reactions ; 

		std::vector<char> r_1 = {'M'} ; 
		std::vector<char> p_1 = {'P'} ;
		Reaction* r1 = new Reaction(r_1,p_1,kn_kplus, 0) ;

		std::vector<char> r_2 = {'M'} ; 
		std::vector<char> p_2 = {'F'} ;
		Reaction* r2 = new Reaction(r_2,p_2,kn_kplus, 1) ;

		reactions.push_back(r1) ; reactions.push_back(r2) ; 

		return Model("Nucleation Elongation,Unseeded", reactions, initial_values) ;
	}


	Model secondary_nucleation() {
		/* Here we have three reactions going on :  
		 * 1. Monomers -> Formation of primary nuclei
		 * 2. Monomers -> Add themselves to Fibril ends 
		 * 3. Moners -> Secondary nucleation 
		*/
		std::map<char, int> initial_values {{'M', 0.000001},{'P', 0} ,{'F', 0}, {'S', 0}};
		std::vector<Reaction*> reactions ; 

		std::vector<char> r_1 = {'M'} ; 
		std::vector<char> p_1 = {'P'} ;
		Reaction* r1 = new Reaction(r_1,p_1,1, 0) ;

		std::vector<char> r_2 = {'M'} ; 
		std::vector<char> p_2 = {'F'} ;
		Reaction* r2 = new Reaction(r_2,p_2,1, 1) ;

		std::vector<char> r_3 = {'M'} ; 
		std::vector<char> p_3 = {'S'} ;
		Reaction* r3 = new Reaction(r_3,p_3,1, 2) ;

		reactions.push_back(r1) ; reactions.push_back(r2) ; reactions.push_back(r3) ;

		return Model("Secondary Nucleation Dominated, Unseeded ", reactions, initial_values) ; 
	}

	Model fragmentation_domination() {
		/* Here we have three reactions :  
		 * 1. Monomers -> Formation of primary nuclei 
		 * 2. Monomers -> Add themselves to Fibril ends 
		 * 3. Fibril -> Fragmentation of fibrils -> reprensented by X 

		 */ 
		std::map<char, int> initial_values {{'M', 0.000001},{'P', 0} ,{'F', 0}, {'X', 0}};
		std::vector<Reaction*> reactions ; 

		std::vector<char> r_1 = {'M'} ; 
		std::vector<char> p_1 = {'P'} ;
		Reaction* r1 = new Reaction(r_1,p_1,1, 0) ;

		std::vector<char> r_2 = {'M'} ; 
		std::vector<char> p_2 = {'F'} ;
		Reaction* r2 = new Reaction(r_2,p_2,1, 1) ;

		std::vector<char> r_3 = {'F'} ; 
		std::vector<char> p_3 = {'X'} ;
		Reaction* r3 = new Reaction(r_3,p_3,1, 2) ;

		reactions.push_back(r1) ; reactions.push_back(r2) ; reactions.push_back(r3) ;

		return Model("Fragmentation dominated, Unseeded", reactions, initial_values) ; 
	}

	Model fragmentation_secondary_nucleation() {
		/* Here we have four reactions :  
		 * 1. Monomers -> Formation of primary nuclei 
		 * 2. Monomers -> Add themselves to Fibril ends 
		 * 3. Monomers -> Secondary nucleation 
		 * 4. Fibril ends -> Fragmented Fibrils 
		*/
		std::map<char, int> initial_values {{'M', 0.000001},{'P', 0} ,{'F', 0}, {'S', 0}, {'X', 0}};
		std::vector<Reaction*> reactions ; 

		std::vector<char> r_1 = {'M'} ; 
		std::vector<char> p_1 = {'P'} ;
		Reaction* r1 = new Reaction(r_1,p_1,1, 0) ;

		std::vector<char> r_2 = {'M'} ; 
		std::vector<char> p_2 = {'F'} ;
		Reaction* r2 = new Reaction(r_2,p_2,1, 1) ;

		std::vector<char> r_3 = {'M'} ; 
		std::vector<char> p_3 = {'S'} ;
		Reaction* r3 = new Reaction(r_3,p_3,1, 2) ;

		std::vector<char> r_4 = {'F'} ; 
		std::vector<char> p_4 = {'X'} ;
		Reaction* r4 = new Reaction(r_4,p_4,1, 2) ;

		reactions.push_back(r1) ; reactions.push_back(r2) ; reactions.push_back(r3) ; reactions.push_back(r4) ;

		return Model("Fragmentation and Secondary Nucleation,Unseeded", reactions, initial_values) ; 
	}

}; 
#endif