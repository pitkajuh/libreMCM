/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "../class/EquationsAddSubtract.h"
#include "../global/global.h"
#include "../math/is_operator.h"
#include "../math/calculate_order_of_operations.h"
#include "../math/is_string_numerical_value.h"
#include "../rcompartment/read_compartment.h"
#include "../rcompartment/get_compartment_index.h"
#include "../util/replace_in_vector.h"
#include "../util/vector_convert.h"
#include "../rcfg/read_bin.h"
#include "../eqs/parse_compartment_equations.h"
#include "../map/create_maps.h"
#include "../wdata/values_to_graph.h"

Equations global_equations;

void params4(int i_replace)
{
  int i=0;
  int size=global_equations.get_size();
  string compartment_parameter_name;
  string compartment_name;
  vector<vector<string>> rt;
  vector<string> global_equation;
  vector<string> equation;
  vector<string> initial_values;

  while(i<=size-1)
    {
      global_equation=global_equations.get(i);
      compartment_name=global_equation[i_replace];

      initial_values=compartment_map_v2[compartment_name];
      compartment_parameter_name=compartment_name+parm_delim+initial_values[i];

      global_equation[i_replace]=compartment_parameter_name;
      global_equations.replace(global_equation, i);

      i++;
    }
  i=0;
}

vector<string> params3(vector<string> equation_vector, int i_replace)
{
  int i=0;
  string compartment_parameter_name;
  string compartment_name=equation_vector[i_replace];
  vector<string> initial_values=compartment_map_v2[compartment_name];

  while(i<=initial_values.size()-1)
    {
      compartment_parameter_name=initial_values[i];
      compartment_parameter_name=compartment_name+parm_delim+compartment_parameter_name;
      equation_vector[i_replace]=compartment_parameter_name;
      global_equations.push_back(equation_vector);
      i++;
    }
  return equation_vector;
}

void params2(vector<int> indices, vector<string> equation_vector, string compartment_name)
{
  int i=0;
  int i_prev;
  int indice;
  int global_equations_size;
  string equation_i;

  while(i<=indices.size()-1)
    {
      indice=indices[i];
      equation_i=equation_vector[indice];
      global_equations_size=global_equations.get_size();

      if(i!=i_prev and global_equations_size>0)
	{
	  params4(indice);
	}
      else
	{
	  equation_vector=params3(equation_vector, indice);
	}
      i_prev=i;
      i++;
    }
}

EquationsAddSubtract replace_param_eq(vector<string> equation_vector, bool equation_add, string compartment_name, int compartment_start_index, int index1)
{
  int i=0;
  int compartment_index;
  int size=equation_vector.size();
  bool operator_or_not;
  bool numerical_value_or_not;
  string eq;
  vector<int> indices;
  EquationsAddSubtract rt;

  while(i<=size-1)
    {
      eq=equation_vector[i];
      operator_or_not=is_operator(eq);
      numerical_value_or_not=is_string_numerical_value(eq);

      if(!operator_or_not and !numerical_value_or_not)
	{
	  compartment_index=get_compartment_index(eq);

	  if(compartment_index!=-1)
	    {
	      indices.push_back(i);
	    }
	}
      i++;
    }
  params2(indices, equation_vector, compartment_name);
  rt.compartment=compartment_name;
  rt.add_equations=equation_add;
  rt.equations=global_equations;
  global_equations.clear();
  return rt;
}
