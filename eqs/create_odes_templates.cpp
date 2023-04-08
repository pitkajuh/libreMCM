/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "get_compartment_indices.h"
#include "../global/global_constants.h"
#include "../global/compartment_total_equations.h"
#include "../global/compartment_indice_data.h"
#include "../global/compartment_map.h"
#include "../global/compartment_map_v2.h"
#include "../global/total_equation_indices.h"
#include "../global/odes_template_data.h"
#include "../global/constant_indice_data.h"
#include "../class/SplittedString.h"
#include "../rcfg/get_constant_value.h"
#include "../math/calculate_equation_constants.h"
#include "../wdata/get_last_value.h"

class Values
{
public:
  vector<string> values;
};

VecVecInt total_equation_indices_t;
bool end=false;
int j=0;
int limit;

vector<string> update_constants(vector<string> equation, const string compartment_name, const int equation_i)
{
  string fchar;
  const vector<string> vec=compartment_map_v2[compartment_name];
  const string initial_value_name=vec[j];
  const IndicesData indices_data=constant_indice_data[equation_i];
  const vector<int> constant_indices=indices_data.indices;

  for(const auto &indice: constant_indices)
    {
      fchar=equation[indice];
      equation[indice]=get_constant_value(fchar, initial_value_name);
    }
  return equation;
}

const vector<Values> get_ivs(const vector<string> compartments)
{
  Values ivs_i;
  vector<string> ivs;
  vector<Values> values;

  for(const auto&compartment: compartments)
    {
      ivs=compartment_map_v2[compartment];
      ivs_i.values=ivs;
      values.push_back(ivs_i);
    }
  return values;
}

void create_ode_template(const vector<string> total_equation, const vector<string> compartments, const vector<int> indices, const vector<int> total_equation_indices_i, const string compartment_name, const int equation_i)
{
  // Uses the total_equation variable (a template) and creates differential equation templates based on the initial values of the compartment.
  int i=0;
  int indice;
  int size2;
  bool ready=false;
  string value;
  string replace;
  string initial_value;
  string ode_i;
  const vector<Values> ivs=get_ivs(compartments);
  const int size=ivs.size()-1;
  Values val;
  vector<string> values;
  vector<string> ode=total_equation;
  vector<string> multiple_last_values_i;
  SplittedString iv_indice_data;
  vector<SplittedString> iv_indices_data_i;

  while(not ready)
    {
      val=ivs[i];
      indice=indices[i];
      values=val.values;
      size2=values.size()-1;
      limit=size2;
      value=values[j];
      ode_i=ode[indice];

      iv_indice_data.splitted_string_part1=ode_i;
      iv_indice_data.splitted_string_part2=value;
      iv_indices_data_i.push_back(iv_indice_data);

      initial_value=get_last_value(iv_indice_data);
      multiple_last_values_i.push_back(initial_value);

      replace=ode_i+PARM_DELIM+value;
      ode[indice]=replace;

      if(i==size)
	{
	  // Simplify the equation here (i.e. if some numerical (constant) values can be calculated). Simplifying the equation here makes the numerical calculation lighter.
	  ode=update_constants(ode, compartment_name, equation_i);
	  ode=calculate_equation_constants(ode);

	  get_compartment_indices(ode); // Update compartment indices after simplifying the equation.
	  odes.push_back(ode);
	  multiple_last_values.push_back(multiple_last_values_i);
	  multiple_last_values_i.clear();

	  iv_indices_data.push_back(iv_indices_data_i);
	  iv_indices_data_i.clear();

	  total_equation_indices_t.push_back(total_equation_indices_i);
	  i=0;
	  ode=total_equation;
	  break;
	}
      i++;
    }
}

void create_odes_templates()
{
  int i=0;
  const int size=compartment_indice_data.size()-1;
  string compartment_name;
  vector<int> indices;
  vector<int> total_equation_indices_i;
  vector<string> compartments;
  vector<string> total_equation;
  IndicesData compartment_indices;
  CompartmentTotalEquation compartment_total_equation;

  while(not end)
    {
      if(i>size)
	{
	  i=0;
	  j++;

	  if(j>limit)
	    {
	      end=true;
	      continue;
	    }
	}

      compartment_indices=compartment_indice_data[i];
      total_equation_indices_i=total_equation_indices[i];
      compartment_total_equation=compartment_total_equations[i];

      compartments=compartment_indices.names;
      indices=compartment_indices.indices;

      compartment_name=compartment_total_equation.compartment_name;
      total_equation=compartment_total_equation.total_equation;
      create_ode_template(total_equation, compartments, indices, total_equation_indices_i, compartment_name, i);
      i++;
    }
  j=0;
  end=false;
  limit=0;
  total_equation_indices.clear();
  total_equation_indices=total_equation_indices_t;
  total_equation_indices_t.clear();
}
