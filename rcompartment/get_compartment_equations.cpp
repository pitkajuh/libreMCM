/*--------------------------------*- C++ -*----------------------------------* \
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <tuple>
#include "../global/global.h"
#include "../rcfg/read_bin.h"
#include "../rcompartment/read_compartment_definition.h"
#include "../rcompartment/read_compartment.h"

using namespace std;

vector<string> calculation_rules_add_to, calculation_rules_subtract_from;
vector<tuple<string, vector<string>, vector<string>>> all_calculation_rules;

vector<string> get_eq_corresponding_to_eq_name(string eq_name)
{
  int i=0;
  vector<string> rt={not_found};
  tuple<string, vector<string>> fchar;
  string eq_name_comp;

  if(eq_name.size()!=0)
    {
      while(i<=equations.size()-1)
	{
	  fchar=equations[i];
	  eq_name_comp=get<0>(fchar);

	  if(eq_name==eq_name_comp)
	    {
	      rt=get<1>(fchar);
	    }
	  i++;

	}
    }

  return rt;
}

string get_source_affecting_equation(vector<vector<string>> compartment_vector, int i_start, int j_start, bool get_horizontal)
{
  int i;
  int j;
  vector<string> equation;
  string rt;
  bool stop=false;
  vector<string> compartment_vector_i;
  string compartment_vector_i_j;
  const string empty_str="";
  string equation_1st;

  if(get_horizontal)
    {
      j=j_start;
      i=0;
    }
  else
    {
      i=i_start;
      j=0;
    }

  while(i<=compartment_vector.size()-1)
    {
      compartment_vector_i=compartment_vector[i];

      while(j<=compartment_vector_i.size()-1)
	{
	  compartment_vector_i_j=compartment_vector[i][j];
	  equation=get_eq_corresponding_to_eq_name(compartment_vector_i_j);
	  equation_1st=equation[0];

	  if(equation_1st!=not_found and compartment_vector_i_j!=empty_str)
	    {
	      if(get_horizontal)
		{
		  rt=compartment_vector_i_j;
		  stop=true;
		  break;
		}
	      else
		{
		  rt=compartment_vector_i_j;
		  stop=true;
		  break;
		}
	    }

	  if(stop)
	    {
	      break;
	    }
	  else if(get_horizontal)
	    {
	      break;
	    }
	  else if(!get_horizontal)
	    {
	      j++;
	    }
	}
      if(stop)
	{
	  break;
	}
      else if(!get_horizontal)
	{
	  break;
	}
      else if(get_horizontal)
	{
	  i++;
	}
    }

  return rt;
}

vector<vector<string>> get_equations_from_compartment_csv(vector<vector<string>> compartment_vector, int i_start, int j_start, bool get_horizontal)
{
  int i;
  int j;
  vector<string> equation;
  string to_compartment;
  vector<vector<string>> equations;
  vector<string> compartment_vector_i;
  string compartment_vector_i_j;
  string equation_1st;

  if(get_horizontal)
    {
      i=i_start;
      j=0;
    }
  else
    {
      j=j_start;
      i=0;
    }

  while(i<=compartment_vector.size()-1)
    {
      compartment_vector_i=compartment_vector[i];

      while(j<=compartment_vector_i.size()-1)
	{
	  compartment_vector_i_j=compartment_vector[i][j];
	  equation=get_eq_corresponding_to_eq_name(compartment_vector_i_j);
	  equation_1st=equation[0];

	  if(equation_1st!=not_found)
	    {
	      to_compartment=get_source_affecting_equation(compartment_vector, i, j, get_horizontal);

	      if(get_horizontal)
		{
		  calculation_rules_add_to.push_back(to_compartment);
		}
	      else
		{
		  calculation_rules_subtract_from.push_back(to_compartment);
		}
	      equations.push_back(equation);
	    }

	  if(!get_horizontal)
	    {
	      break;
	    }
	  else if(get_horizontal)
	    {
	      j++;
	    }
	}
      if(get_horizontal)
	{
	  break;
	}
      else if(!get_horizontal)
	{
	  i++;
	}
    }

  return equations;
}

tuple<string, vector<vector<string>>, vector<vector<string>>> get_equations_compartment(vector<vector<string>> compartment_vector, string compartment, int i_start, int j_start)
{
  bool add_bool=true;
  bool subtract_bool=false;

  vector<vector<string>> equations_subtract=get_equations_from_compartment_csv(compartment_vector, i_start, j_start, add_bool);
  vector<vector<string>> equations_add=get_equations_from_compartment_csv(compartment_vector, i_start, j_start, subtract_bool);
  tuple<string, vector<string>, vector<string>> calc_rule=make_tuple(compartment, calculation_rules_add_to, calculation_rules_subtract_from);
  all_calculation_rules.push_back(calc_rule);
  calculation_rules_add_to.clear();
  calculation_rules_subtract_from.clear();
  tuple<string, vector<vector<string>>, vector<vector<string>>> rt=make_tuple(compartment, equations_add, equations_subtract);
  return rt;
}

tuple<vector<string>, int> get_target_compartments(string compartment_name, bool add_or_not, int i_start)
{
  int i=i_start;
  string compartment_name_compare;
  vector<string> target_compartments;
  tuple<string, vector<string>, vector<string>> calculation_rule;
  tuple<vector<string>, int> rt;

  while(i<=all_calculation_rules.size()-1)
    {
      calculation_rule=all_calculation_rules[i];
      compartment_name_compare=get<0>(calculation_rule);

      if(compartment_name==compartment_name_compare)
	{
	  i_start=i;

	  if(add_or_not)
	    {
	      target_compartments=get<1>(calculation_rule);
	    }
	  else
	    {
	      target_compartments=get<2>(calculation_rule);
	    }
	  break;
	}
      i++;
    }

  rt=make_tuple(target_compartments, i_start);

  return rt;
}
