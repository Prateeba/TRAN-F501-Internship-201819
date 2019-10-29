#include "../include/rangen.h"
#include <math.h>       /* log */
std::mt19937 rng_engine;

RanGen::RanGen(){
    unsigned long int rng_seed=0;

    std::ifstream filein;
    std::ofstream fileout;
    fileout.open("seed.out");
    filein.open("seed.in");

    if (!filein)   
    {

        std::random_device sysrand;
        rng_seed=sysrand();

        rng_engine.seed(rng_seed); //seed RNGengine

        fileout <<rng_seed<<std::endl;
        fileout.close();
        //std::cout <<"#seed.in not found. Creating a new seed: "<<rng_seed<<std::endl;
    }
    else
    {
        //std::cout<<"#reading seed.in"<<std::endl;
        filein >> rng_seed;
        fileout <<rng_seed<<std::endl;

        //srandom(seed);
        rng_engine.seed(rng_seed); //seed RNGengine
        fileout.close();
        filein.close();
    }


}

bool RanGen::ranbool(){
        std::uniform_int_distribution<int> distribution(0,1);
        int result= distribution(rng_engine);
	return (result == 0)? false : true;
}

int RanGen::ranval(int min, int max){
        std::uniform_int_distribution<int> distribution(min,max);
	return distribution(rng_engine);
}

double RanGen::randouble(){
    std::uniform_real_distribution<double> distribution(0.0,1.0);
    return distribution(rng_engine);
}


double RanGen::rangauss(double sigma){
    std::normal_distribution<double> distribution(0.0,sigma);
    return distribution(rng_engine);
}


int RanGen::ranpoisson(double mu){
    std::poisson_distribution<int> distribution(mu);
    return distribution(rng_engine);
}
		
double RanGen::ranpoissonpdf(unsigned int /*k*/, double mu){
    return ranpoisson(mu);
}

double RanGen::ranexp(double lamda) {
    double u = randouble() ; 
    return -log(u)/lamda ; 
}