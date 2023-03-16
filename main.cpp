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

int main()
{
  vector<string> list_of_models=read_model_data();
  auto begin2=std::chrono::high_resolution_clock::now();

  for(const auto&i: list_of_models)
    {
      auto begin=std::chrono::high_resolution_clock::now();
      cout<<"Starting "<<i<<'\n';
      get_compartments(i);
      get_compartment_parameters(i);
      get_bin(i);
      get_sim_params(i);
      parse_compartment_equations_subroutine();
      parse_compartment_equations();
      parse_compartment_eqs_for_num_calc();
      get_equations_for_numerical_calculation();
      numerical_calculation_begin();
      calculate();
      runge_kutta();
      write_to_file(i);

      auto end=std::chrono::high_resolution_clock::now();
      auto duration=std::chrono::duration_cast<std::chrono::milliseconds>(end-begin);
      cout<<"Runtime: "<<duration.count()<<" milliseconds"<<'\n';
      cout<<"################################################################"<<'\n';
    }
  auto end2=std::chrono::high_resolution_clock::now();
  auto duration2=std::chrono::duration_cast<std::chrono::milliseconds>(end2-begin2);
  cout<<"Total runtime: "<<duration2.count()<<" milliseconds"<<'\n';
  return 0;
}
