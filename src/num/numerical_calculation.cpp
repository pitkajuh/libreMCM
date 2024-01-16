/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "k.h"
#include "rk4_helpers.h"
#include "../global/h.h"
#include "../global/t.h"
#include "../global/global_constants.h"
#include "../global/compartment_map.h"
#include "../global/t_start.h"
#include "../global/t_end.h"
#include "../global/step_size.h"
#include "../global/odes.h"
#include "../global/num_method.h"
#include "../global/num_methods.h"
#include "../global/ode_indice_operator.h"
#include "../eqs/update_iv.h"

#include <iostream>
using std::iostream;
using std::cout;
using std::to_string;

const vector<double> get_values()
{
  double value;
  vector<double> rt;
  vector<string> vec1;
  map<string, map<string, vector<string>>>::reverse_iterator compartment_map_begin=compartment_map.rbegin();
  map<string, map<string, vector<string>>>::reverse_iterator compartment_map_end=compartment_map.rend();
  map<string, vector<string>>::iterator parameter_map_end;
  map<string, vector<string>>::iterator parameter_map_begin;
  map<string, vector<string>> parameter_map_i;

  while(compartment_map_begin!=compartment_map_end)
    {
      parameter_map_i=compartment_map_begin->second;
      parameter_map_end=parameter_map_i.end();
      parameter_map_begin=parameter_map_i.begin();

      while(parameter_map_begin!=parameter_map_end)
	{
	  vec1=parameter_map_begin->second;
	  value=stod(vec1.back());
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
  string compartment_name;
  string parameter_name;
  vector<string> vec;
  map<string, map<string, vector<string>>>::reverse_iterator compartment_map_begin=compartment_map.rbegin();
  map<string, map<string, vector<string>>>::reverse_iterator compartment_map_end=compartment_map.rend();
  map<string, vector<string>>::iterator parameter_map_begin;
  map<string, vector<string>>::iterator parameter_map_end;
  map<string, vector<string>> parameter_map_i;

  while(compartment_map_begin!=compartment_map_end)
    {
      compartment_name=compartment_map_begin->first;
      parameter_map_i=compartment_map_begin->second;
      parameter_map_end=parameter_map_i.end();
      parameter_map_begin=parameter_map_i.begin();

      while(parameter_map_begin!=parameter_map_end)
	{
	  parameter_name=parameter_map_begin->first;
	  vec=parameter_map_begin->second;
	  vec.push_back(result[i]);
	  parameter_map_i[parameter_name]=vec;
	  parameter_map_begin++;
	  i++;
	}
      compartment_map[compartment_name]=parameter_map_i;
      compartment_map_begin++;
    }
}

const vector<string> update_equations_subroutine(vector<string> equation, const vector<int> indices, const vector<string> values_to_add, const int index)
{
  int i=0;
  int indice;
  const int size=indices.size()-1;
  string compartment_name;
  string result;
  SplittedString eq_params_i;
  const vector<SplittedString> eq_params=param_data[index];
  const vector<IndiceOperatorData> data=ode_indice_operator[index];

  while(i<=size)
    {
      indice=indices[i];
      eq_params_i=eq_params[i];
      compartment_name=eq_params_i.splitted_string_part1;
      result=get_value(compartment_name, values_to_add);
      equation[indice]=update_iv(result, data, indice);
      i++;
    }
  return equation;
}

void update_equations(const vector<string> values_to_add)
{
  int i=0;
  const int size=equations.size()-1;
  vector<int> indice;
  vector<string> equation;
  Equations rt;

  while(i<=size)
    {
      equation=equations[i];
      indice=indice_values[i];
      equations[i]=update_equations_subroutine(equation, indice, values_to_add, i);
      i++;
    }
}

const vector<string> calculate_result(const vector<double> k1, const vector<double> k2, const vector<double> k3, const vector<double> k4, const vector<double> get_values_up)
{
  int i=0;
  const int size=k1.size()-1; // k1, k2, k3 and k4 have equal sizes.
  double k1_i;
  double k2_i;
  double k3_i;
  double k4_i;
  double value;
  string result;
  vector<string> rt;

  while(i<=size)
    {
      value=get_values_up[i];
      k1_i=k1[i];
      k2_i=k2[i];
      k3_i=k3[i];
      k4_i=k4[i];
      result=to_string(value+(k1_i+2*k2_i+2*k3_i+k4_i)/6);
      rt.push_back(result);
      i++;
    }
  return rt;
}

void rk4()
{
  vector<double> k1;
  vector<double> k2;
  vector<double> k3;
  vector<double> k4;
  vector<double> get_val;
  vector<string> result;
  h=step_size;

  cout<<"Start calculation"<<'\n';

   while(t<=t_end+h)
    {
      k1=k0();
      k2=k(k1, 0.5);
      k3=k(k2, 0.5);
      k4=k(k3, 0);
      get_val=get_values();
      result=calculate_result(k1, k2, k3, k4, get_val);
      update_equations(result);
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
