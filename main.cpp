/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <iostream>
#include <chrono>
#include "rcompartment/read_compartment.h"
#include "rcompartment/get_compartment_parameters.h"
#include "rcfg/get_sim_params.h"
#include "rcfg/read_model_data.h"
#include "rcfg/get_bin.h"
#include "eqs/parse_compartment_equations.h"
#include "eqs/parse_compartment_eqs_for_num_calc.h"
#include "num/numerical_calculation_begin.h"
#include "num/numerical_calculation.h"
#include "wdata/write_to_file.h"

using std::iostream;
using std::cout;
using std::endl;

int main()
{
  int i=0;
  vector<string> list_of_models=read_model_data();
  string model;
  auto begin2=std::chrono::high_resolution_clock::now();

  while(i<=list_of_models.size()-1)
    {
      model=list_of_models[i];
      cout<<"Running model: "<<model<<endl;

      get_compartments(model);
      get_compartment_parameters(model);
      get_bin(model);
      get_sim_params(model);
      parse_compartment_equations_subroutine();
      parse_compartment_equations();
      parse_compartment_eqs_for_num_calc();
      get_equations_for_numerical_calculation();
      numerical_calculation_begin();
      calculate();
      auto begin=std::chrono::high_resolution_clock::now();
      runge_kutta();
      auto end=std::chrono::high_resolution_clock::now();
      auto duration=std::chrono::duration_cast<std::chrono::milliseconds>(end-begin);
      cout<<"Runtime: "<<duration.count()<<" milliseconds"<<endl;
      write_to_file(model);
      i++;
    }
  auto end2=std::chrono::high_resolution_clock::now();
  auto duration2=std::chrono::duration_cast<std::chrono::milliseconds>(end2-begin2);
  cout<<"Total runtime: "<<duration2.count()<<" milliseconds"<<endl;
  return 0;
}
