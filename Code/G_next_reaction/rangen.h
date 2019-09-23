#ifndef __RANGEN_H_
#define __RANGEN_H_

#include <random>
#include <iostream>
#include <fstream>

extern std::mt19937 rng_engine;

class RanGen {
    public:
        //constructor
        RanGen();
        //methods
        bool ranbool();
        double randouble();	
        
        /** returns random integer in [min,max]. */
        int ranval(int min, int max);	
        double rangauss(double);
        int ranpoisson(double);
        double ranpoissonpdf(unsigned int, double);
        double rancauchypdf(unsigned int, double);
};

#endif