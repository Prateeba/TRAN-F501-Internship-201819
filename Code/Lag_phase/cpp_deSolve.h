/**
 * File: cpp_deSolve.h
 * Utilities for solving the differential equations of compartmental 
   epidemic models using 4th order Runge-Kutta
 * Author: Sherry Towers smtowers@asu.edu
 * Created: Feb 21st, 2013
 * Copyright Sherry Towers, 2013
*/


#include <iostream>
#include <vector>
using namespace std;

class cpp_deSolve{
private:
	std::vector<double> _InitialValues;
	std::vector<double> _Parameters;
	int                 _ModelType;

/** method to calculate the derivatives wrt time
 * if ModelType==1 this will solve an SIR model
    _IntialValues in order S, I, R
    _Parameters   in order beta, gamma

 * if ModelType==2 this will solve an SEIR model
    _IntialValues in order S, E, I, R
    _Parameters   in order beta, kappa, gamma

 * if ModelType==3 this will solve a harmonic SIR model
    _IntialValues in order S, I, R
    _Parameters   in order beta0, epsilon, phi, gamma

 * if ModelType==4 this will solve the model equations you code up
                 in the ModelEquations method in cpp_deSolve.cpp
    you supply the compartments in the order you want
    and the parameter vector in the order you want */
	void ModelEquations(double mytime, std::vector<double>  ModelEstimates ,std::vector<double>& Derivatives);

/** Runge-Kutta method for solving differential equations */
	void RungeKuttaSolver(double time_step,double mytime, std::vector<double> oldModelEstimates, std::vector<double>& newModelEstimates);

public:
	cpp_deSolve(std::vector<double> InitialValues, std::vector<double> Parameters, int ModelType);
	~cpp_deSolve();
 
/** 
 * ModelEstimates[i][j] has i going from 0 to length(vtime)-1 and j going from 0 to # of compartments-1
 * ModelEstimatesTranspose[j][i] has i going from 0 to length(vtime)-1 and j going from 0 to # of compartments-1  */
	void SimulateModel(std::vector<double> vtime, std::vector<std::vector<double> >& ModelEstimates, std::vector<std::vector<double> >& ModelEstimatesTranspose);
	void SimulateModel(std::vector<double> vtime, std::vector<std::vector<double> >& ModelEstimates);
};
