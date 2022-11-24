/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <tuple>
#include "is_operator.h"
#include "replace_in_vector.h"
#include "read_bin.h"
#include "calculate_order_of_operations.h"
#include "parse_compartment_equations.h"

using namespace std;

vector<string> equation_str_to_vec(string equation)
{
  int i=0;
  string empty="", fchar;
  vector<string> rt;

  while(i<=equation.size()-1)
    {
      fchar=equation[i];
      if(is_operator(fchar))
	{
	  rt.push_back(empty);
	  rt.push_back(fchar);
	  empty="";
	}
      else
	{
	  empty=empty+fchar;
	}
      i++;
    }
  rt.push_back(empty);

  return rt;
}

int get_compartment_index(string compartment_name)
{
  int i=0, compartment_index;
  bool found=false;

  while(i<=equations_with_compartment_name.size()-1)
    {
      if(compartment_name==get<0>(equations_with_compartment_name[i]))
	{
	  compartment_index=i;
	  found=true;
	  break;
	}
      i++;
    }

  if(equations_with_compartment_name.size()-1 and !found)
    {
      compartment_index=-1;
    }

  return compartment_index;
}

void calculate_with_parameters(vector<string> equation_vector, int calculate_from_index, int calculate_to_index, string compartment_name)
{
  int half_life, j=0, compartment_index=get_compartment_index(compartment_name);
  string parameter_name, parameter_value, compartment_name_change;

  if(compartment_index!=-1)
    {
      int i=compartment_index;
      string compartment_name_compare=get<0>(all_values[compartment_index]);
      vector<tuple<string, string, int>> parameters=get<1>(all_values[compartment_index]);

      while(i<=all_values.size()-1)
	{
	  compartment_name_change=get<0>(all_values[i]);

	  if(compartment_name_change==compartment_name)
	    {
	      while(j<=get<1>(all_values[i]).size()-1)
		{
		  compartment_name_change=get<0>(all_values[i]);
		  parameter_name=get<0>(parameters[j]);
		  parameter_value=get<1>(parameters[j]);
		  half_life=get<2>(parameters[j]);
		  j++;
		}
	      j=0;
	    }
	  i++;
	}
    }
}

vector<tuple<string, string, int>> get_compartment_elements_by_compartment_name(string compartment_name)
{
  int i=0, j=0;
  vector<tuple<string, string, int>> compartment_values;

  while(i<=all_values.size()-1)
    {
      if(compartment_name==get<0>(all_values[i]))
	{
	  compartment_values=get<1>(all_values[i]);
	  break;
	}
      i++;
    }

  return compartment_values;
}

vector<vector<string>> global_equations;
int start_from=0;

void params4(vector<tuple<string, string, int>> compartments_parameters, int index_replace)
{
  int i=0;
  string compartment_parameter_name;
  vector<vector<string>> rt;

  while(i<=global_equations.size()-1)
    {
      compartment_parameter_name=get<0>(compartments_parameters[i]);
      global_equations[i]=replace_in_vector(global_equations[i], compartment_parameter_name, index_replace, index_replace);
      i++;
    }
}

vector<string> params3(vector<tuple<string, string, int>> compartments_parameters, vector<string> equation_vector, int index_replace)
{
  int i=0;
  i=start_from;
  string compartment_parameter_name;
  vector<vector<string>> rt;

  while(i<=compartments_parameters.size()-1)
    {
      compartment_parameter_name=get<0>(compartments_parameters[i]);
      equation_vector=replace_in_vector(equation_vector, compartment_parameter_name, index_replace, index_replace);
      global_equations.push_back(equation_vector);
      i++;
    }
  return equation_vector;
}

int j_global=0;

void params2(vector<int> indices, vector<string> equation_vector, vector<vector<tuple<string, string, int>>> compartments_parameters)
{
  int i=0, j=0, equation_vector_size=equation_vector.size ();
  vector<vector<string>> rt1;
  vector<tuple<string, string, int>> compartment_values, parameters;
  int i_prev;

  while(i<=indices.size()-1)
    {
      parameters=get_compartment_elements_by_compartment_name(equation_vector[indices[i]]);

      if(i!=i_prev and global_equations.size()>=1)
	{
	  params4(parameters, indices[i]);
	}
      else
	{
	  equation_vector=params3(parameters, equation_vector, indices[i]);
	}
      i_prev=i;
      i++;
    }
}

tuple<string, bool, vector<vector<string>>> abc(string equation, bool equation_add, string compartment_name, int compartment_start_index, int index1)
{
  vector<string> equation_vector=equation_str_to_vec(equation);
  int i=0;
  int j=index1;
  int index_get_from_other_compartment; //, equation_vector_size=equation_vector.size();
  vector<tuple<string, string, int>> compartment_values, parameters;

  int compartment_index;
  string empty2, eq;
  int found=0;
  vector<vector<string>> eqs;
  vector<vector<vector<string>>> eqs1;
  vector<int> indices;

  vector<
    vector<tuple<string, string, int>>
    > compartments_parameters;

  tuple<string, bool, vector<vector<string>>> rt;

  while(i<=equation_vector.size()-1)
    {
      eq=equation_vector[i];
      if(!is_operator(eq) and !is_string_numerical_value(eq))
	{
	  compartment_index=get_compartment_index(eq);
	  if(compartment_index!=-1)
	    {
	      indices.push_back (i);
	    }
	}
      i++;
    }

  j_global=0;
  params2(indices, equation_vector, compartments_parameters);
  rt=make_tuple (compartment_name, equation_add, global_equations);
  global_equations.clear();
  return rt;
}
