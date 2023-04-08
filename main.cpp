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
#include "rcfg/get_sim_params.h"
#include "rcfg/read_model_data.h"
#include "rcfg/get_bin.h"
#include "rcompartment/get_compartment.h"
#include "rcompartment/get_compartment_parameters.h"
#include "rcompartment/get_compartment_equations.h"
#include "map/create_initial_value_map.h"
#include "map/create_compartment_target_map.h"
#include "map/create_compartment_maps.h"
#include "eqs/parse_compartment_equations.h"
#include "eqs/replace_indices.h"
#include "eqs/create_odes_templates.h"
#include "eqs/create_odes.h"
#include "num/numerical_calculation.h"
#include "wdata/parse_initial_values.h"
#include "wdata/clear_data.h"
#include "wdata/write_to_file.h"

using std::cout;

int total_duration;

int main()
{
  vector<string> list_of_models=read_model_data();

  for(const auto&i: list_of_models)
    {
      auto begin=std::chrono::high_resolution_clock::now();
      cout<<"Starting "<<i<<'\n';

      get_compartment(i);
      get_bin(i);
      get_sim_params(i);
      get_compartment_parameters(i);
      get_compartment_equations();
      create_target_compartment_map();
      create_initial_value_map();
      parse_initial_values();
      create_compartment_map();
      parse_compartment_equations();
      replace_indices();
      create_odes_templates();
      create_odes();
      numerical_calculation_start();
      write_to_file(i);
      clear_data();

      auto end=std::chrono::high_resolution_clock::now();
      auto duration=std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
      cout<<"Runtime: "<<duration.count()<<" microseconds "<<(double)duration.count()/1000<<" milliseconds"<<'\n';
      total_duration=total_duration+duration.count();
      cout<<"################################################################"<<'\n';
    }

  cout<<"Total runtime: "<<total_duration<<" microseconds "<<(double)total_duration/1000<<" milliseconds"<<'\n';
  return 0;
}
