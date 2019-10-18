//#######################################################################
// A C++ program to provide examples of use of methods
// in the deSolve class to numerically
// solve an SIR model
//
// Author: Sherry Towers
//         smtowers@asu.edu
// Created: Mar 22nd, 2013
//
// Copyright Sherry Towers, 2013
//
// This program is not guaranteed to be free of bugs and/or errors.
//
// This program can be freely used and shared, as long as the author information
// and copyright in the header remains intact.
//#######################################################################
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <iostream>
#include "cpp_deSolve.h"

//################################################################################
//################################################################################
using namespace std;
int main(int argc, char **argv){

  //##############################################################################
  // Let's solve the model for times t=0 to 100 in steps of 1/100th of a day
  // Note that you need to make the time step quite small in order for this 
  // method to work!
  //##############################################################################
  double mytime = 0.0;
  double delta_t = 0.010;
  vector<double> vtime;
  while (mytime<=(100.0+delta_t)){
     vtime.push_back(mytime);
     mytime = mytime + delta_t;
  }

  //##############################################################################
  // fill vectors with the parameters and the initial values
  //##############################################################################
  double beta = 0.50;
  double gamma = 0.20;
  vector<double> Parameters;
  Parameters.push_back(beta);
  Parameters.push_back(gamma);

  double npop = 100000;
  double I_0 = 1.0;
  double S_0 = npop-I_0;
  double R_0 = 0.0;
  vector<double> InitialValues;
  InitialValues.push_back(S_0);
  InitialValues.push_back(I_0);
  InitialValues.push_back(R_0);
  
  //##############################################################################
  // ModelType==1 is an SIR model
  //##############################################################################
  int ModelType = 1;
  cpp_deSolve mysir(InitialValues
                   ,Parameters
                   ,ModelType);

  //##############################################################################
  // now solve the model using the Runge Kutta method
  //##############################################################################
  vector<vector<double> > ModelEstimates;
  mysir.SimulateModel(vtime
                     ,ModelEstimates);

  for (int i=0;i<vtime.size();i++){
     cout << vtime[i] << " ";
     for (int j=0;j<InitialValues.size();j++){
        cout << ModelEstimates[i][j] << " ";
     }
     cout << endl;
  }
 
  return 0;

} // end program
