#ifndef DEF_FITTER
#define DEF_FITTER
#include <iostream>
#include <cstddef>
#include <string>
#include <limits>
#include <vector>
#include <map>

class Fitter {
private : 
	std::vector<std::vector<std::string>> results  ; // contains the data 

public :
	Fitter(std::vector<std::vector<std::string>> r) :results(r) {}
	std::vector<std::vector<double>> normalize(std::vector<std::vector<std::string>>, int, int , int) ;  
} ; 



#endif 