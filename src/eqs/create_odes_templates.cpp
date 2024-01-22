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
#include "../global/compartment_total_equations.h"
#include "../global/compartment_indice_data.h"
#include "../global/compartment_map.h"
#include "../global/compartment_map_v2.h"
#include "../global/total_equation_indices.h"
#include "../global/odes_template_data.h"
#include "../global/constant_indice_data.h"
#include "../global/ode_indice_operator_prev.h"
#include "../global/ode_indice_operator.h"
#include "../class/SplittedString.h"
#include "../rcfg/get_constant_value.h"
#include "../math/calculate_equation_constants.h"
#include "../math/calculate_order_of_operations.h"
#include "../math/is_variable.h"
#include "../math/is_constant.h"
#include "../wdata/get_last_value.h"
#include "../util/string_split.h"
#include "../util/vector_convert.h"

using std::to_string;

struct Values
{
  vector<string> values;
};

VecVecInt total_equation_indices_t;
bool end=false;
int j=0;
int limit;

void indice_operator_data_update(vector<string> ode_upd, vector<string> ode_not_upd, const int index)
{
  int i=0;
  int j=0;
  int i_data;
  const int size_upd=ode_upd.size()-1;
  bool variable_check;
  string upd_i;
  string not_upd_i;
  string compartment;
  string dummy=" ";
  vector<IndiceOperatorData> data=ode_indice_operator_prev[index];
  vector<IndiceOperatorData> data2=data;
  vector<IndiceOperatorData> new_data;
  const int size_data=data.size()-1;
  IndiceOperatorData data_i;
  SplittedString splitted;

  while(i<=size_data)
    {
      data_i=data[i];
      i_data=data_i.index;
      not_upd_i=ode_not_upd[i_data];

      while(j<=size_upd)
	{
	  upd_i=ode_upd[j];
	  splitted=string_split(upd_i, PARM_DELIM);
	  compartment=splitted.splitted_string_part1;
	  variable_check=is_variable(compartment);

	  if(not_upd_i==upd_i and variable_check)
	    {
	      data_i.index=j;
	      new_data.push_back(data_i);
	      ode_upd[j]=dummy;
	      ode_not_upd[i_data]=dummy;
	      break;
	    }
	  j++;
	}
      j=0;
      i++;
    }
  ode_indice_operator.push_back(new_data);
}

string parse_constant(const string constant, const string initial_value_name, const int index, const int data_index)
{
  int i=0;
  vector<string> constant_vec=equation_string_to_equation_vector(constant);
  const int size=constant_vec.size()-1;
  bool is_negative=false;
  bool constant_check;
  string fchar;
  string constant_value;

  while(i<=size)
    {
      fchar=constant_vec[i];
      constant_check=is_constant(fchar);

      if(constant_check)
	{
	  constant_value=get_constant_value(fchar, initial_value_name);
	  constant_vec[i]=constant_value;
	}
      i++;
    }
  constant_vec=calculate_order_of_operations(constant_vec);
  constant_value=constant_vec.back();
  return constant_value;
}

string constant_value_update(string constant, const string initial_value_name, const int index, const int data_index)
{
  int i=0;
  int index_check;
  string value=parse_constant(constant, initial_value_name, index, data_index);
  vector<IndiceOperatorData> operator_data=ode_indice_operator_prev[data_index];
  IndiceOperatorData data_i;
  const int size=operator_data.size()-1;

  while(i<=size)
    {
      data_i=operator_data[i];
      index_check=data_i.index;

      if(index_check==index)
	{
	  data_i.index_value=value;
	  value=data_i.get_result();
	  break;
	}
      i++;
    }
  return value;
}

vector<string> update_constants(vector<string> equation, const string compartment_name, const int equation_i)
{
  string fchar;
  string value;
  const vector<string> vec=compartment_map_v2[compartment_name];
  const string initial_value_name=vec[j];
  const IndicesData indices_data=constant_indice_data[equation_i];
  const vector<int> constant_indices=indices_data.indices;

  for(const auto &i: constant_indices)
    {
      fchar=equation[i];
      value=constant_value_update(fchar, initial_value_name, i, equation_i);
      equation[i]=value;
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
  // Uses the total_equation variable (a template) and creates differential equation templates based on the initial values of the compartment. One differential equation will be generated for each initial value.
  int i=0;
  int indice;
  int size2;
  string value;
  string replace;
  string initial_value;
  string ode_i;
  const vector<Values> ivs=get_ivs(compartments);
  const int size=ivs.size()-1;
  Values val;
  vector<string> values;
  vector<string> ode=total_equation;
  vector<string> ode_not_upd;
  vector<string> multiple_last_values_i;
  SplittedString iv_indice_data;
  vector<SplittedString> iv_indices_data_i;

  while(not end)
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
	  // Simplify the equation here (i.e. if some numerical (constant) values can be calculated). Simplifying the equation here makes the numerical calculation faster.
	  ode=update_constants(ode, compartment_name, equation_i);
	  ode_not_upd=ode;
	  ode=calculate_equation_constants(ode);

	  // Update indice operator data, because indices may change due to simplifying the equation.
	  indice_operator_data_update(ode, ode_not_upd, equation_i);
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
