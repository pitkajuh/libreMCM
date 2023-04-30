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
#include "global/probabilistic.h"
#include "bin/run_deterministic.h"
#include "rcfg/read_model_data.h"
#include "rcfg/get_sim_params.h"
#include "rcfg/get_bin.h"
#include "eqs/replace_indices.h"
#include "rcompartment/get_compartment.h"
#include "rcompartment/get_compartment_parameters.h"
#include "rcompartment/get_compartment_equations.h"
#include "map/create_initial_value_map.h"
#include "map/create_compartment_target_map.h"
#include "map/create_compartment_maps.h"
#include "eqs/parse_compartment_equations.h"
#include "wdata/parse_initial_values.h"

using std::cout;

int total_duration;

int main()
{
  const vector<string> list_of_models=read_model_data();

  for(const auto&model: list_of_models)
    {
      auto begin=std::chrono::high_resolution_clock::now();
      cout<<"Starting "<<model<<'\n';

      get_bin(model);
      get_sim_params(model);
      get_compartment(model);
      get_compartment_parameters(model);
      get_compartment_equations();
      create_target_compartment_map();
      create_initial_value_map();
      parse_initial_values();
      create_compartment_map();
      parse_compartment_equations();
      replace_indices();

      if(probabilistic)
	{
	  // WIP
	}
      else
	{
	  run_deterministic(model);
	  auto end=std::chrono::high_resolution_clock::now();
	  auto duration=std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
	  cout<<"Runtime: "<<duration.count()<<" microseconds "<<(double)duration.count()/1000<<" milliseconds"<<'\n';
	  total_duration=total_duration+duration.count();
	}
      cout<<"Total runtime: "<<total_duration<<" microseconds "<<(double)total_duration/1000<<" milliseconds"<<'\n';
      cout<<"################################################################"<<'\n';
    }
  return 0;
}
