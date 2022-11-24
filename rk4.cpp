/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "numerical_calculation.h"
#include "rk4_helpers.h"
#include "calculate_order_of_operations.h"
#include "replace_in_vector.h"
#include "is_operator.h"
#include "string_split.h"
#include "get_compartment_equations.h"

using namespace std;

bool rk4_debug=false;
vector<string> vector_add, vector_subtract;
int i_start=0, is_in_indices_start_index=0, nr_of_runs=0;
string compartment_name_local_global;
vector<string> global_compartment_names;

vector<string> k_calc(vector<vector<string>> equations, vector<vector<int>> indices, vector<string> values_to_add, string constant, vector<vector<string>> param_data, vector<vector<int>> numerical_calculation_order_of_operations)
{
  int i=0;
  double result;
  vector<string> rt;

  while(i<=equations.size()-1)
    {
      result=h*k_test(equations[i], indices[i], values_to_add, constant, param_data, numerical_calculation_order_of_operations[i]);
      rt.push_back(to_string(result));
      i++;
    }

  asd=0;
  return rt;
}

tuple<vector<string>, vector<int>, bool, vector<string>> rk4_start(vector<string> equation, string compartment_name, bool add_or_not)
{
  int i=0, j=0;
  string fchar, replace, subtract_from_compartment, add_to_compartment;
  int equation_size=equation.size();
  tuple<vector<string>, int> target_compartments_all;
  vector<string> target_compartments, comps1;
  vector<int> indices_for_ks;
  tuple<string, string> param1;

  while(i<=equation_size-1)
    {
      fchar=equation[i];

      if(!is_string_numerical_value(equation[i]) and get_compartment_index(compartment_name)!=-1 and !is_operator(equation[i]))
	{
	  target_compartments_all=get_target_compartments(compartment_name, add_or_not, i_start);
	  target_compartments=get<0>(target_compartments_all);
	  i_start=get<1>(target_compartments_all);

	  while(j<=target_compartments.size()-1)
	    {
	      if(target_compartments[j]==origin_element and !add_or_not)
		{
		  subtract_from_compartment=target_compartments[j];
		  add_to_compartment=compartment_name;
		}
	      else
		{
		  subtract_from_compartment=target_compartments[j];
		  add_to_compartment=compartment_name;
		}
	      j++;
	    }
	  j=0;
	  param1=split_string_in_two(fchar, parm_delim);
	  indices_for_ks.push_back(i);
	  replace=get_compartment_parameter_value(fchar);
	  comps1.push_back(fchar);
	  equation=replace_in_vector(equation, replace, i, i);
	  equation_size=equation.size();
	}
      i++;
    }

  return make_tuple(equation, indices_for_ks, add_or_not, comps1);
}

vector<tuple<string, tuple<vector<string>, vector<int>, vector<string>>, vector<int>, vector<string>, vector<string>>> solution_prepare(string compartment_name, vector<vector<string>> equations_add_all, vector<vector<string>> equations_subtract_all)
{
  int i=0, j=0;
  vector<string> equation1;
  vector<tuple<vector<string>, vector<int>, bool, vector<string>>> vector1;
  compartment_name_local_global=compartment_name;
  global_compartment_names.push_back(compartment_name_local_global);

  if(equations_add_all.size()>=1)
    {
      while(i<=equations_add_all.size()-1)
	{
	  equation1=equations_add_all[i];
	  vector1.push_back(rk4_start(equation1, compartment_name, true));
	  i++;
	}
    }



  if(equations_subtract_all.size()>=1)
    {
      while(j<=equations_subtract_all.size()-1)
	{
	  equation1=equations_subtract_all[j];
	  vector1.push_back(rk4_start(equation1, compartment_name, false));
	  j++;
	}
    }

  vector<
  tuple<string,
       tuple<vector<string>, vector<int>, vector<string>>, //final_eq
       vector<int>, // indices_for_ks
       vector<string>, // multiple_last_values
       vector<string> // parameter_data_for_indices
       >
    > data1;

  tuple<vector<string>, vector<int>, vector<string>> final_eq=combine_equations_and_indices(vector1);
  vector<string> equation=get<0>(final_eq), parameter_data_for_indices=get<2>(final_eq), multiple_last_values=get_multiple_last_values(parameter_data_for_indices);
  vector<int> indices_for_ks=get<1>(final_eq);

  data1.push_back(make_tuple(compartment_name, final_eq, indices_for_ks, multiple_last_values, parameter_data_for_indices));
  return data1;
}
