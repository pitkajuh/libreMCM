/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "../class/SplittedString.h"
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
#include "../debug/debug.h"

Equations global_equations;

void params4(const int i_replace)
{
  int i=0;
  const int size=global_equations.size();
  string compartment_parameter_name;
  string compartment_name;
  string initial_value;
  vector<string> global_equation;
  vector<string> equation;
  vector<string> initial_values;
  SplittedString compartment_initial_value;

  while(i<=size-1)
    {
      global_equation=global_equations[i];
      compartment_name=global_equation[i_replace];

      initial_values=compartment_map_v2[compartment_name];
      initial_value=initial_values[i];
      compartment_initial_value.splitted_string_part1=compartment_name;
      compartment_initial_value.splitted_string_part2=initial_value;
      compartment_parameter_name=compartment_name+PARM_DELIM+initial_value;

      global_equation[i_replace]=compartment_parameter_name;
      global_equations[i]=global_equation;
      i++;
    }
}

void params3(vector<string> equation_vector, const int i_replace)
{
  string name;
  string compartment_name=equation_vector[i_replace];
  vector<string> initial_values=compartment_map_v2[compartment_name];
  const int size=initial_values.size();
  SplittedString compartment_initial_value;

  for(const auto&i: initial_values)
    {
      name=compartment_name+PARM_DELIM+i;
      compartment_initial_value.splitted_string_part1=compartment_name;
      compartment_initial_value.splitted_string_part2=i;
      equation_vector[i_replace]=name;
      global_equations.push_back(equation_vector);
    }
}

void params2(const vector<int> indices, const vector<string> equation_vector)
{
  int i=0;
  int i_prev;
  int indice;
  int global_equations_size;
  const int size=indices.size();
  string equation_i;

  while(i<=size-1)
    {
      indice=indices[i];
      equation_i=equation_vector[indice];
      global_equations_size=global_equations.size();

      if(i!=i_prev and global_equations_size>0)
	{
	  params4(indice);
	}
      else
	{
	  params3(equation_vector, indice);
	}
      i_prev=i;
      i++;
    }
}

EquationsAddSubtract replace_param_eq(const vector<string> equation, const bool equation_add, const string compartment_name)
{
  int i=0;
  int compartment_index;
  const int size=equation.size();
  bool operator_or_not;
  bool numerical_value_or_not;
  string eq;
  vector<int> indices;
  EquationsAddSubtract rt;

  while(i<=size-1)
    {
      eq=equation[i];
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
  params2(indices, equation);
  rt.compartment=compartment_name;
  rt.add_equations=equation_add;
  rt.equations=global_equations;
  global_equations.clear();
  return rt;
}
