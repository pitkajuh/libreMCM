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

vector<vector<vector<string>>> equations_add, equations_subtract;
vector<vector<string>> equations_add_all, equations_subtract_all;
int int_add=0, int_subtract=0;

void push_to_all_equations(vector<vector<vector<string>>> equations, bool add_or_not)
{
  int i=0, j=0;

  while(i<=equations.size()-1)
    {
      while(j<=equations[i].size()-1)
	{

	  if(add_or_not)
	    {
	      equations_add_all.push_back(equations[i][j]);
	    }
	  else
	    {
	      equations_subtract_all.push_back(equations[i][j]);
	    }
	  j++;
	}
      j=0;
      i++;
    }
}

void get_equations_for_numerical_calculation()
{
  int i=0, j=0, k=0;
  string compartment_name;
  vector<vector<vector<string>>> equations_add_1, equations_subtract_1;

  while(i<=equations_for_calculation.size()-1)
    {
      compartment_name=get<0>(equations_for_calculation[i]);
      equations_add_1=get<1>(equations_for_calculation[i]);
      equations_subtract_1=get<2>(equations_for_calculation[i]);

      if(equations_add_1.size()>0 and equations_subtract_1.size()>0)
	{
	  push_to_all_equations(equations_add_1, true);
	  push_to_all_equations(equations_subtract_1, false);

	  final_equations_for_calculation.push_back(make_tuple(compartment_name, equations_add_all, equations_subtract_all));

	  equations_add_all.clear();
	  equations_subtract_all.clear();
	}
      i++;
    }
}

void add_equations_for_numerical_calculation(string compartment_name)
{
  if(int_add==1 and int_subtract==1)
    {
      equations_for_calculation.push_back(make_tuple(compartment_name, equations_add, equations_subtract));
      equations_add.clear();
      equations_subtract.clear();
    }
  else if(int_add==2)
    {
      equations_for_calculation.push_back(make_tuple(compartment_name, equations_add, equations_subtract));
      equations_add.clear();
      equations_subtract.clear();
    }
  else if(int_subtract==2)
    {
      equations_for_calculation.push_back(make_tuple(compartment_name, equations_add, equations_subtract));
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
  bool add_equation, add_equation_previous; // if 1, equation add material to compartment, if 0 they remove material from compartment
  vector<vector<string>> equations, equations_to_parse;
  vector<string> equations2, eqs1, rt1;
  vector<tuple<string, bool, vector<vector<string>>>> rt=rt_local_global;
  bool last=false;
  bool first_comp=false;
  string compartment_name_previous1;

  while(i<=rt.size()-1)
    {
      eqs=rt[i];
      compartment_name=get<0>(eqs);

      if (!first_comp)
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
