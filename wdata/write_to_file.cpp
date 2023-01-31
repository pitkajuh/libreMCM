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
#include "values_to_graph.h"
#include "../global/global.h"
#include "../rcfg/read_bin.h"
#include "../num/numerical_calculation.h"
#include "../num/numerical_calculation_begin.h"
#include "../util/string_split.h"
#include "../eqs/parse_compartment_equations.h"

using namespace std;

void write_to_file(string directory)
{
  int i=0;
  int j=0;
  int k=0;
  double t=0;
  string str;
  string compartment_name;
  vector<tuple<string, vector<string>>> parameters_data;
  tuple<string, vector<string>> parameter;
  string parameter_name;
  vector<string> parameter_values;
  bool ready=false;
  string parameter_values_k;
  tuple<
    string, // compartment name
    vector<
      tuple<
	string, // parameter name
	vector<
	  string // parameter values
	  >
	>     >      >
    params_graph_up_i;
  const string empty_str="";
  const string str_new_row="\n";
  const string file_type=".txt";
  string t_str;
  string header="t"+delimiter;
  bool write_header=true;
  tuple<string, string> parameter_name_splitted;
  string save_path;

  while(i<=params_graph_up.size()-1)
    {
      params_graph_up_i=params_graph_up[i];
      compartment_name=get<0>(params_graph_up_i);
      parameters_data=get<1>(params_graph_up_i);
      save_path=directory+compartment_name+file_type;
      ofstream myfile(save_path);
      write_header=true;

      while(!ready)
	{
	  parameter=parameters_data[j];
	  parameter_name=get<0>(parameter);
	  parameter_name_splitted=split_string_in_two(parameter_name, parm_delim);
	  parameter_name=get<1>(parameter_name_splitted);
	  parameter_values=get<1>(parameter);
	  parameter_values_k=parameter_values[k];

	  if(k==parameter_values.size()-1)
	    {
	      ready=true;
	    }
	  else if(parameters_data.size()-1==0)
	    {
	      if(write_header)
		{
		  header=header+parameter_name+str_new_row;
		  write_header=false;
		}

	      t_str=to_string(t);
	      str=str+t_str+delimiter+parameter_values_k;
	      str=str+str_new_row;
	      k++;
	      t=t+h;
	    }
	  else if(j==0 and parameters_data.size()-1!=0)
	    {
	      if(write_header)
		{
		  header=header+parameter_name+delimiter;
		}

	      t_str=to_string(t);
	      str=str+t_str+delimiter+parameter_values_k+delimiter;
	      j++;
	    }
	  else if(j==parameters_data.size()-1)
	    {
	      str=str+parameter_values_k;

	      if(write_header)
		{
		  header=header+parameter_name+str_new_row;
		  write_header=false;
		}

	      str=str+str_new_row;
	      j=0;
	      k++;
	      t=t+h;
	      continue;
	    }
	  else
	    {
	      if(write_header)
		{
		  header=header+parameter_name+delimiter;
		}

	      str=str+parameter_values_k+delimiter;
	      j++;
	    }
	}

      ready=false;
      myfile<<header;
      myfile<<str;
      str=empty_str;
      header="t"+delimiter;
      myfile.close();
      j=0;
      k=0;
      t=0;
      i++;
    }

  params_graph_up.clear();
  params_graph.clear();
  variables.clear();
  equations.clear();
  equations_with_compartment_name.clear();
  all_values.clear();
  for_calculation.clear();
}
