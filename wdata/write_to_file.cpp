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
#include <fstream>
#include "values_to_graph.h"
#include "../global/global.h"
#include "../rcfg/read_bin.h"
#include "../num/rk4.h"
#include "../num/numerical_calculation.h"
#include "../num/numerical_calculation_begin.h"
#include "../map/create_maps.h"
#include "../util/string_split.h"
#include "../eqs/parse_compartment_equations.h"
#include "../eqs/parse_compartment_eqs_for_num_calc.h"
#include "../rcompartment/read_compartment.h"
#include "../rcompartment/read_compartment_definition.h"
#include "../rcompartment/get_compartment_equations.h"

using std::cout;
using std::endl;
using std::ofstream;
using std::to_string;

void write_to_file(string directory)
{
  int i=0;
  int j=0;
  int k=0;
  double t=0;
  const string str_new_row="\n";
  const string file_type=".txt";
  const string header_const="t"+delimiter;
  string header=header_const;
  string line="";
  string t_str;
  string save_path;
  string compartment_name;
  string initial_value_name;
  string value;
  bool ready=false;
  vector<string> initial_value_names;
  vector<string> value_vector;
  map<string, map<string, vector<string>>>::reverse_iterator begin=compartment_map.rbegin();
  map<string, map<string, vector<string>>>::reverse_iterator end=compartment_map.rend();
  map<string, vector<string>> values;

  cout<<"Writing results"<<endl;

  while(begin!=end)
    {
      compartment_name=begin->first;
      save_path=directory+compartment_name+file_type;
      ofstream myfile(save_path);
      initial_value_names=compartment_map_v2[compartment_name];
      values=compartment_map[compartment_name];

      // Create header line containing initial value names (t;iv1;iv2;iv3...)
      while(i<=initial_value_names.size()-1)
	{
	  initial_value_name=initial_value_names[i];
	  if(initial_value_names.size()==1)
	    {
	      header=header+initial_value_name+str_new_row;
	    }
	  else if(i==initial_value_names.size()-1)
	    {
	      header=header+initial_value_name+str_new_row;
	    }
	  else
	    {
	      header=header+initial_value_name+delimiter;
	    }
	  i++;
	}
      while(!ready)
	{
	  initial_value_name=initial_value_names[j];
	  value_vector=values[initial_value_name];
	  value=value_vector[k];

	  if(initial_value_names.size()==1)
	    {
	      // Write result when there are only one initial value in each compartment.
	      if(j==initial_value_names.size()-1 and k==value_vector.size()-1)
		{
		  ready=true;
		  break;
		}
	      else if(k<=value_vector.size()-1)
		{
		  t_str=to_string(t);
		  line=line+t_str+delimiter+value+str_new_row;
		  t=t+h;
		  k++;
		  continue;
		}
	    }
	  else
	    {
	      // Write result when there are more than one initial value in each compartment.
	      if(k==value_vector.size()-1 and j==initial_value_names.size()-1)
		{
		  line=line+delimiter+value;
		  ready=true;
		}
	      else if(j<=initial_value_names.size()-1)
		{
		  if(j==0)
		    {
		      t_str=to_string(t);
		      line=line+t_str+delimiter+value;
		    }
		  else if(j==initial_value_names.size()-1)
		    {
		      line=line+delimiter+value+str_new_row;
		      k++;
		      t=t+h;
		      j=0;
		      continue;
		    }
		  else
		    {
		      line=line+delimiter+value;
		    }
		}
	    }
	  j++;
	}
      // Write header and results to file
      myfile<<header;
      myfile<<line;

      ready=false;
      i=0;
      j=0;
      k=0;
      t=0;
      line="";
      header=header_const;
      begin++;
    }

  all_compartments.clear();
  all_parameters.clear();
  initial_values_all.clear();
  equations.clear();
  equations_map.clear();
  constants.clear();
  for_calculation.clear();
  parameter_map.clear();
  compartment_map_v2.clear();
  compartment_map.clear();
  compartment_target_map.clear();
  equations_with_compartment_name.clear();
  all_values.clear();
  rt_local_global.clear();
  compartment_diagonal.clear();
  compartment_diagonal_v2.clear();
  row_map.clear();
  column_map.clear();
  compartment_parameters.clear();
  compartment_parameters_rt.clear();
  compartments_and_equations.clear();
  global_compartment_names.clear();
  final_equations_for_calculation.clear();
  equations_add_all.clear();
  equations_subtract_all.clear();
}
