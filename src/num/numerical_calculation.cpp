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
  vector<double> rt;
  vector<string> vec;
  unordered_map<string, vector<string>> p_map_i;

  for(auto i=compartment_map.begin(); i!=compartment_map.end(); i++)
    {
      p_map_i=i->second;

      for(auto j=p_map_i.begin(); j!=p_map_i.end(); j++)
	{
	  vec=j->second;
	  rt.push_back(stod(vec.back()));
	}
    }
  return rt;
}

void update_values(const vector<string> result)
{
  int i=0;
  string compartment_name;
  string parameter_name;
  vector<string> vec;
  unordered_map<string, vector<string>> p_map_i;

  for(auto j=compartment_map.begin(); j!=compartment_map.end(); j++)
    {
      compartment_name=j->first;
      p_map_i=j->second;

      for(auto k=p_map_i.begin(); k!=p_map_i.end(); k++)
	{
	  parameter_name=k->first;
	  vec=k->second;
	  vec.push_back(result[i]);
	  p_map_i[parameter_name]=vec;
	  i++;
	}
      compartment_map[compartment_name]=p_map_i;
    }
}

const vector<string> update_equations_subroutine(vector<string> equation, const vector<int> indices, const vector<string> add, const int index)
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
      result=get_value(compartment_name, add);
      equation[indice]=update_iv(result, data, indice);
      i++;
    }
  return equation;
}

void update_equations(const vector<string> add)
{
  int i=0;
  const int size=equations.size()-1;
  vector<int> indice;
  vector<string> equation;

  while(i<=size)
    {
      equation=equations[i];
      indice=indice_values[i];
      equations[i]=update_equations_subroutine(equation, indice, add, i);
      i++;
    }
}

void rk4()
{
  K_vec k1;
  K_vec k2;
  K_vec k3;
  K_vec k4;
  K_vec w1;
  vector<string> result;
  h=step_size;
  cout<<"Start calculation"<<'\n';

  while(t<=t_end+h)
    {
      k1.t1=k0();
      k2.t1=k(k1, 0.5);
      k3.t1=k(k2, 0.5);
      k4.t1=k(k3, 0);
      w1.t1=get_values();
      w1=w1+(k1+(k2+k3)*2+k4)/6;
      result=w1.to_str();
      update_equations(result);
      update_values(result);
      t+=h;
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
  if(num_method==RK4){rk4();}
}
