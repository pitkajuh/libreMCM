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
#include "get_compartment_equations.h"
#include "parse_compartment_equations.h"

using namespace std;

vector<tuple<string, vector<vector<string>>, vector<vector<string>>>> final_equations_for_calculation;

vector<
  tuple<
    string, // Compartment name.
    vector<vector<vector<string>>>, // Equations which add material to the compartment. Equations are given in vector form.
    vector<vector<vector<string>>> // Equations which remove/subtract material from the compartment. Equations are given in vector form.
    >
  > equations_for_calculation;

vector<vector<vector<string>>> equations_add;
vector<vector<vector<string>>> equations_subtract;
vector<vector<string>> equations_add_all;
vector<vector<string>>  equations_subtract_all;
int int_add=0;
int int_subtract=0;

void push_to_all_equations(vector<vector<vector<string>>> equations, bool add_or_not)
{
  int i=0;
  int j=0;
  vector<vector<string>> equations_i;
  vector<string> equations_i_j;

  while(i<=equations.size()-1)
    {
      equations_i=equations[i];

      while(j<=equations_i.size()-1)
	{
	  equations_i_j=equations[i][j];

	  if(add_or_not)
	    {
	      equations_add_all.push_back(equations_i_j);
	    }
	  else
	    {
	      equations_subtract_all.push_back(equations_i_j);
	    }
	  j++;
	}
      j=0;
      i++;
    }
}

void get_equations_for_numerical_calculation()
{
  int i=0;
  string compartment_name;
  vector<vector<vector<string>>> equations_add_1;
  vector<vector<vector<string>>> equations_subtract_1;
  tuple<string, vector<vector<string>>, vector<vector<string>>> final_equation_i;

  tuple<
    string, // Compartment name.
    vector<vector<vector<string>>>, // Equations which add material to the compartment. Equations are given in vector form.
    vector<vector<vector<string>>> // Equations which remove/subtract material from the compartment. Equations are given in vector form.
    >
   equations_for_calculation_i;

  while(i<=equations_for_calculation.size()-1)
    {
      equations_for_calculation_i=equations_for_calculation[i];
      compartment_name=get<0>(equations_for_calculation_i);
      equations_add_1=get<1>(equations_for_calculation_i);
      equations_subtract_1=get<2>(equations_for_calculation_i);

      if(equations_add_1.size()>0 and equations_subtract_1.size()>0)
	{
	  push_to_all_equations(equations_add_1, true);
	  push_to_all_equations(equations_subtract_1, false);
	  final_equation_i=make_tuple(compartment_name, equations_add_all, equations_subtract_all);
	  final_equations_for_calculation.push_back(final_equation_i);
	  equations_add_all.clear();
	  equations_subtract_all.clear();
	}
      i++;
    }
}

void add_equations_for_numerical_calculation(string compartment_name)
{
  tuple<
    string, // Compartment name.
    vector<vector<vector<string>>>, // Equations which add material to the compartment. Equations are given in vector form.
    vector<vector<vector<string>>> // Equations which remove/subtract material from the compartment. Equations are given in vector form.
    >
   equations_for_calculation_i1;

  tuple<
    string, // Compartment name.
    vector<vector<vector<string>>>, // Equations which add material to the compartment. Equations are given in vector form.
    vector<vector<vector<string>>> // Equations which remove/subtract material from the compartment. Equations are given in vector form.
    >
   equations_for_calculation_i2;

  tuple<
    string, // Compartment name.
    vector<vector<vector<string>>>, // Equations which add material to the compartment. Equations are given in vector form.
    vector<vector<vector<string>>> // Equations which remove/subtract material from the compartment. Equations are given in vector form.
    >
   equations_for_calculation_i3;

  if(int_add==1 and int_subtract==1)
    {
      equations_for_calculation_i1=make_tuple(compartment_name, equations_add, equations_subtract);
      equations_for_calculation.push_back(equations_for_calculation_i1);
      equations_add.clear();
      equations_subtract.clear();
    }
  else if(int_add==2)
    {
      equations_for_calculation_i2=make_tuple(compartment_name, equations_add, equations_subtract);
      equations_for_calculation.push_back(equations_for_calculation_i2);
      equations_add.clear();
      equations_subtract.clear();
    }
  else if(int_subtract==2)
    {
      equations_for_calculation_i3=make_tuple(compartment_name, equations_add, equations_subtract);
      equations_for_calculation.push_back(equations_for_calculation_i3);
      equations_add.clear();
      equations_subtract.clear();
    }
  //  Does not yet take into account if int_subtract=0 and int_add=1, or int_subtract=1 and int_add=0
}

void add_or_subtract_equations(vector<vector<string>> rt1, bool add_equation, string compartment_name)
{
  if(add_equation)
    {
      equations_add.push_back(rt1);
      // Equations add material to system.
      int_add++;
    }
  else
    {
      equations_subtract.push_back(rt1);
      // Equations subtract material from the system.
      int_subtract++;
    }
}

void parse_compartment_eqs_for_num_calc()
{
  int i=0;
  tuple<string, bool, vector<vector<string>>> eqs;
  string compartment_name;
  bool add_equation;
  bool add_equation_previous; // if 1, equation add material to compartment, if 0 they remove material from compartment
  vector<vector<string>> equations;
  vector<vector<string>> equations_to_parse;
  vector<tuple<string, bool, vector<vector<string>>>> rt=rt_local_global;
  bool last=false;
  bool first_comp=false;
  string compartment_name_previous1;

  while(i<=rt.size()-1)
    {
      eqs=rt[i];
      compartment_name=get<0>(eqs);

      if(!first_comp)
	{
	  compartment_name_previous1=compartment_name;
	  first_comp=true;
	}

      add_equation=get<1>(eqs);
      equations=get<2>(eqs);

      if(i==rt.size()-1 and !last)
	{
	  i--;
	  last=true;
	  continue;
	}

      if(compartment_name_previous1!=compartment_name)
	{
	  add_equations_for_numerical_calculation(compartment_name_previous1);
	  int_add=0;
	  int_subtract=0;
	}
      else
	{
	  add_or_subtract_equations(equations, add_equation, compartment_name);
	}

      compartment_name_previous1=compartment_name;
      i++;
    }

  add_equations_for_numerical_calculation(compartment_name_previous1);

  int_add=0;
  int_subtract=0;

  get_equations_for_numerical_calculation();
}
