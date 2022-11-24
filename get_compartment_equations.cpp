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
#include "global.h"
#include "read_bin.h"
#include "read_compartment_definition.h"
#include "read_compartment.h"

using namespace std;

vector<string> calculation_rules_add_to, calculation_rules_subtract_from;
vector<tuple<string, vector<string>, vector<string>>> all_calculation_rules;

string get_eq_corresponding_to_eq_name(string eq_name)
{
  int i=0;
  string rt=not_found;

  if (eq_name.size ()!=0)
    {
      while(i<=equations.size()-1)
	{
	  if(eq_name==get<0>(equations[i]))
	    {
	      rt=get<1>(equations[i]);
	    }
	  i++;
	}
    }

  return rt;
}

string get_source_affecting_equation(vector<vector<string>> compartment_vector, int i_start, int j_start, bool get_horizontal)
{
  int i, j;
  string equation, rt;
  bool stop=false;

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
      while(j<=compartment_vector[i].size()-1)
	{
	  equation=get_eq_corresponding_to_eq_name(compartment_vector[i][j]);

	  if(equation==not_found and compartment_vector[i][j]!="")
	    {
	      if(get_horizontal)
		{
		  rt=compartment_vector[i][j];
		  stop=true;
		  break;
		}
	      else
		{
		  rt=compartment_vector[i][j];
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

vector<string> get_equations_from_compartment_csv(vector<vector<string>> compartment_vector, int i_start, int j_start, bool get_horizontal)
{
  int i, j;
  string equation, to_compartment;
  vector<string> equations;

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
      while(j<=compartment_vector[i].size()-1)
	{
	  equation=get_eq_corresponding_to_eq_name(compartment_vector[i][j]);

	  if(equation!=not_found)
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

tuple<string, vector<string>, vector<string>> get_equations_compartment(vector<vector<string>> compartment_vector, string compartment, int i_start, int j_start)
{
  string equation_subtract, equation_add;
  vector<string> equations_subtract, equations_add;

  equations_subtract=get_equations_from_compartment_csv(compartment_vector, i_start, j_start, true);
  equations_add=get_equations_from_compartment_csv(compartment_vector, i_start, j_start, false);

  all_calculation_rules.push_back(make_tuple(compartment, calculation_rules_add_to, calculation_rules_subtract_from));

  calculation_rules_add_to.clear();
  calculation_rules_subtract_from.clear();

  return make_tuple(compartment, equations_add, equations_subtract);
}

tuple<vector<string>, int> get_target_compartments(string compartment_name, bool add_or_not, int i_start)
{
  int i=i_start, i_continue_from;
  string compartment_name_compare;
  vector<string> target_compartments;

  while(i<=all_calculation_rules.size()-1)
    {
      compartment_name_compare=get<0>(all_calculation_rules[i]);

      if(compartment_name==compartment_name_compare)
	{
	  i_start=i;

	  if(add_or_not)
	    {
	      target_compartments=get<1>(all_calculation_rules[i]);
	    }
	  else
	    {
	      target_compartments=get<2>(all_calculation_rules[i]);
	    }
	  break;
	}
      i++;
    }

  return make_tuple(target_compartments, i_start);
}
