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
#include "rk4_helpers.h"
#include "k.h"
#include "../class/SplittedStrings.h"
#include "../global/h.h"
#include "../global/t.h"
#include "../global/global_constants.h"
#include "../global/compartment_diagonal.h"
#include "../global/compartment_diagonal_v2.h"
#include "../global/compartment_map.h"
#include "../global/t_start.h"
#include "../global/t_end.h"
#include "../global/step_size.h"
#include "../global/odes.h"
#include "../global/num_method.h"
#include "../global/num_methods.h"

using std::to_string;
using std::cout;

const vector<string> get_values()
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
	  value=vec1.back();
	  rt.push_back(value);
	  parameter_map_begin++;
	}
      compartment_map_begin++;
    }
  return rt;
}

void update_values(const vector<string> result)
{
  int i=0;
  const int size=result.size()-1;
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

const vector<string> update_equations_subroutine(vector<string> equation, const vector<int> indices, const vector<string> values_to_add, const SplittedStrings param_data, const int index)
{
  int i=0;
  int indice;
  const int size=indices.size()-1;
  bool is_negative;
  string compartment_name;
  string result;
  SplittedString eq_params_i;
  const vector<SplittedString> eq_params=param_data[index];

  while(i<=size)
    {
      indice=indices[i];
      eq_params_i=eq_params[i];
      compartment_name=eq_params_i.splitted_string_part1;
      result=get_value(compartment_name, values_to_add);
      equation[indice]=result;
      i++;
    }
  return equation;
}

const Equations update_equations(Equations equations, const VecVecInt indices, const vector<string> values_to_add, const SplittedStrings param_data)
{
  int i=0;
  const int size=equations.size()-1;
  vector<int> indice;
  vector<string> update_eq_sub;
  vector<string> equation;
  Equations rt;

  while(i<=size)
    {
      equation=equations[i];
      indice=indices[i];
      update_eq_sub=update_equations_subroutine(equation, indice, values_to_add, param_data, i);
      rt.push_back(update_eq_sub);
      i++;
    }
  return rt;
}

const string calculate_k_value(const string k1, const string k2, const string k3, const string k4, const string get_values_up)
{
  const double k1_i=stod(k1);
  const double k2_i=stod(k2);
  const double k3_i=stod(k3);
  const double k4_i=stod(k4);
  const double value_update=stod(get_values_up);
  const double result_double1=(k1_i+2*k2_i+2*k3_i+k4_i)/6;
  const double result_double=value_update+result_double1;
  const string result=to_string(result_double);
  return result;
}

const vector<string> calculate_result(const vector<string> k1, const vector<string> k2, const vector<string> k3, const vector<string> k4, const vector<string> get_values_up)
{
  int i=0;
  const int size=k1.size()-1; // k1, k2, k3 and k4 have equal sizes.
  string k1_i;
  string k2_i;
  string k3_i;
  string k4_i;
  string get_values_up_i;
  string result_str;
  vector<string> rt;

  while(i<=size)
    {
      get_values_up_i=get_values_up[i];
      k1_i=k1[i];
      k2_i=k2[i];
      k3_i=k3[i];
      k4_i=k4[i];
      result_str=calculate_k_value(k1_i, k2_i, k3_i, k4_i, get_values_up_i);
      rt.push_back(result_str);
      i++;
    }
  return rt;
}

void rk4()
{
  const string HALF="0.5";
  const vector<string> EMPTY={" "};
  vector<string> k1;
  vector<string> k2;
  vector<string> k3;
  vector<string> k4;
  vector<string> result;
  vector<string> get_val;
  h=step_size;
  t_end=t_end+h;

  cout<<"Start calculation "<<'\n';

   while(t<=t_end)
    {
      k1=k(equations, indice_values, EMPTY, ZERO, param_data, math_op_indices);
      k2=k(equations, indice_values, k1, HALF, param_data, math_op_indices);
      k3=k(equations, indice_values, k2, HALF, param_data, math_op_indices);
      k4=k(equations, indice_values, k3, ZERO, param_data, math_op_indices);
      get_val=get_values();
      result=calculate_result(k1, k2, k3, k4, get_val);
      equations=update_equations(equations, indice_values, result, param_data);
      update_values(result);
      t=t+h;
    }
  t=0;
  math_op_indices.clear();
  equations.clear();
  indice_values.clear();
  param_data.clear();
  cout<<"Calculation ready"<<'\n';
}

void numerical_calculation_start()
{
  // Select numerical calculation method.
  if(num_method==RK4)
    {
      rk4();
    }
}
