/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <string>
#include <vector>
#include "rk4.h"
#include "numerical_calculation_rules.h"
#include "numerical_calculation_begin.h"
#include "../class/Data.h"
#include "../rcompartment/read_compartment.h"
#include "../eqs/equations_sort.h"
#include "../wdata/values_to_graph.h"
#include "../map/create_maps.h"
#include "../global/global.h"
#include "../util/replace_in_vector.h"
#include "../util/string_split.h"
#include "../math/calculate_order_of_operations.h"
#include "../rcfg/read_sim_params.h"

using std::string;
using std::vector;
using std::to_string;

double h;
string comp_name_glob;
int jk=0;
int comp=0;

VecVecInt numerical_calculation_order_of_operations;
VecVecInt numerical_calculation_order_of_operations_sorted;
VecVecInt indice_values_sorted;
Equations equations_sorted;
VecVecString param_data_sorted;

void update_values(vector<string> result)
{
  int i=0;
  string name;
  string result_k;
  string compartment_name;
  string parameter_name;
  vector<string> vec1;
  map<string, map<string, vector<string>>>::reverse_iterator compartment_map_begin=compartment_map.rbegin();
  map<string, map<string, vector<string>>>::reverse_iterator compartment_map_end=compartment_map.rend();
  map<string, vector<string>>::iterator parameter_map_begin;
  map<string, vector<string>>::iterator parameter_map_end;
  map<string, vector<string>> parameter_map_i;

  while(compartment_map_begin!=compartment_map_end)
    {
      compartment_name=compartment_map_begin->first;
      parameter_map_i=compartment_map[compartment_name];
      parameter_map_end=parameter_map_i.end();
      parameter_map_begin=parameter_map_i.begin();

      while(parameter_map_begin!=parameter_map_end)
	{
	  parameter_name=parameter_map_begin->first;
	  vec1=parameter_map_i[parameter_name];
	  result_k=result[i];
	  vec1.push_back(result_k);
	  parameter_map_i[parameter_name]=vec1;
	  parameter_map_begin++;
	  i++;
	}
      compartment_map[compartment_name]=parameter_map_i;
      compartment_map_begin++;
    }
}

string update_equations_sub_sub_routine(string compartment_name_find, vector<string> params)
{
  int i=0;
  int size=compartment_diagonal_v2.size();
  int indice_found;
  string compartment_name;
  string params_rt;

  while(i<=size-1)
    {
      compartment_name=compartment_diagonal_v2[i];

      if(compartment_name_find==compartment_name)
	{
	  indice_found=i;
	  break;
	}
      i++;
    }
  params_rt=params[indice_found];
  return params_rt;
}

vector<string> update_equations_subroutine(vector<string> equation, vector<int> indices, vector<string> values_to_add, VecVecString param_data)
{
  int i=0;
  int size=indices.size();
  string compartment_name_split;
  string equations_updated;
  vector<string> eq_params=param_data.get(jk);
  string eq_params_i;
  int indice;
  SplittedString string_splitted;

  while(i<=size-1)
    {
      indice=indices[i];
      eq_params_i=eq_params[i];
      string_splitted=split_string_in_two(eq_params_i, parm_delim);
      compartment_name_split=string_splitted.splitted_string_part1;

      equations_updated=update_equations_sub_sub_routine(compartment_name_split, values_to_add);
      equation[indice]=equations_updated;
      i++;
    }
  jk++;
  return equation;
}

Equations update_equations(Equations equations, VecVecInt indices, vector<string> values_to_add, VecVecString param_data)
{
  int i=0;
  int size=equations.get_size();
  Equations rt;
  vector<string> update_eq_sub;
  vector<string> equation;
  vector<int> indice;

  while(i<=size-1)
    {
      equation=equations.get(i);
      indice=indices.get(i);
      update_eq_sub=update_equations_subroutine(equation, indice, values_to_add, param_data);
      rt.push_back(update_eq_sub);
      i++;
    }
  return rt;
}

vector<string> get_values()
{
  string parameter_name;
  string compartment_name;
  string value;
  vector<string> rt;
  vector<string> vec1;
  map<string, map<string, vector<string>>>::reverse_iterator compartment_map_begin=compartment_map.rbegin();
  map<string, map<string, vector<string>>>::reverse_iterator compartment_map_end=compartment_map.rend();
  map<string, vector<string>>::iterator parameter_map_end;
  map<string, vector<string>>::iterator parameter_map_begin;
  map<string, vector<string>> parameter_map_i;

  while(compartment_map_begin!=compartment_map_end)
    {
      compartment_name=compartment_map_begin->first;
      parameter_map_i=compartment_map[compartment_name];
      parameter_map_end=parameter_map_i.end();
      parameter_map_begin=parameter_map_i.begin();

      while(parameter_map_begin!=parameter_map_end)
	{
	  parameter_name=parameter_map_begin->first;
	  vec1=parameter_map_i[parameter_name];
	  value=vec1[vec1.size()-1];
	  rt.push_back(value);
	  parameter_map_begin++;
	}
      compartment_map_begin++;
    }
  return rt;
}

vector<string> calculate_result(vector<string> k1, vector<string> k2, vector<string> k3, vector<string> k4, double h, vector<string> get_values_up)
{
  int i=0;
  vector<string> rt;
  string get_values_up_i;
  string result_str;
  string k1_i;
  string k2_i;
  string k3_i;
  string k4_i;
  double k1_i_double;
  double k2_i_double;
  double k3_i_double;
  double k4_i_double;
  double result;
  double value_update;

  while(i<=k1.size()-1)
    {
      get_values_up_i=get_values_up[i];
      value_update=stod(get_values_up_i);
      k1_i=k1[i];
      k2_i=k2[i];
      k3_i=k3[i];
      k4_i=k4[i];
      k1_i_double=stod(k1_i);
      k2_i_double=stod(k2_i);
      k3_i_double=stod(k3_i);
      k4_i_double=stod(k4_i);

      result=value_update+(k1_i_double+2*k2_i_double+2*k3_i_double+k4_i_double)/6;
      result_str=to_string(result);
      rt.push_back(result_str);
      i++;
    }
  return rt;
}

void calculate()
{
  int i=0;
  int j=0;
  int size=for_calculation.get_size();
  int size_i;
  string comp_name_glob;
  vector<Solution> aa;
  Solution bb;
  vector<string> equation;
  vector<string> parameter_data_for_indices;
  vector<int> indices_for_ks;
  vector<int> calc_rules;
  Equations equations;
  VecVecInt indice_values;
  VecVecString param_data;
  EquationsIndices final_eq;

  while(i<=size-1)
    {
      aa=for_calculation.get(i);
      comp_name_glob=global_compartment_names[i];
      size_i=aa.size();

      while(j<=size_i-1)
	{
	  bb=aa[j];
	  final_eq=bb.final_eq1;

	  equation=final_eq.equation;
	  indices_for_ks=final_eq.indices;
	  parameter_data_for_indices=final_eq.parameter_data;

	  calc_rules=numerical_calculation_rules(equation);
	  numerical_calculation_order_of_operations.push_back(calc_rules);
	  equations.push_back(equation);
	  indice_values.push_back(indices_for_ks);
	  param_data.push_back(parameter_data_for_indices);
	  j++;
	}
      j=0;
      i++;
    }

  Data sorted1=equations_sort(equations, numerical_calculation_order_of_operations, indice_values, param_data);

  equations_sorted=sorted1.equations_sorted;
  numerical_calculation_order_of_operations_sorted=sorted1.calc_order_sorted;
  indice_values_sorted=sorted1.indice_values_sorted;
  param_data_sorted=sorted1.param_data_sorted;
}

void runge_kutta()
{
  vector<string> k1;
  vector<string> k2;
  vector<string> k3;
  vector<string> k4;
  vector<string> result;
  vector<string> get_val;
  const vector<string> empty_vector={" "};
  const string zero_value="0";
  const string half_value="0.5";
  h=steps;
  double t=t_start;

  while(t<=t_end-h)
    {
      k1=k(equations_sorted, indice_values_sorted, empty_vector, zero_value, param_data_sorted, numerical_calculation_order_of_operations_sorted);
      k2=k(equations_sorted, indice_values_sorted, k1, half_value, param_data_sorted, numerical_calculation_order_of_operations_sorted);
      k3=k(equations_sorted, indice_values_sorted, k2, half_value, param_data_sorted, numerical_calculation_order_of_operations_sorted);
      k4=k(equations_sorted, indice_values_sorted, k3, zero_value, param_data_sorted, numerical_calculation_order_of_operations_sorted);
      get_val=get_values();
      comp=0;
      result=calculate_result(k1, k2, k3, k4, h, get_val);

      equations_sorted=update_equations(equations_sorted, indice_values_sorted, result, param_data_sorted);
      update_values(result);
      jk=0;
      t=t+h;
    }

  t=0;
  jk=0;
  comp=0;
  numerical_calculation_order_of_operations.clear();
  equations_sorted.clear();
  numerical_calculation_order_of_operations_sorted.clear();
  indice_values_sorted.clear();
  param_data_sorted.clear();
}