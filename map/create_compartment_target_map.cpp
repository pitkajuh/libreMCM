/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <algorithm>
#include "../global/compartment_target_map.h"
#include "../global/compartments_and_equations_map.h"
#include "../class/TargetCompartments.h"
#include "../global/global_constants.h"
#include "../global/compartment_diagonal.h"
#include "../util/is_in_vector.h"

string find_compartment(const string equation_name, const string compartment_name)
{
  string compartment;
  string result;
  bool adding;
  bool subtracting;
  vector<string> equations_add;
  vector<string> equations_subtract;
  EquationNamesAddSubtract compartment_and_equations;
  map<string, EquationNamesAddSubtract>::iterator begin=compartments_and_equations.begin();
  map<string, EquationNamesAddSubtract>::iterator end=compartments_and_equations.end();

  while(begin!=end)
    {
      compartment=begin->first;

      if(compartment_name!=compartment)
	{
	  compartment_and_equations=compartments_and_equations[compartment];
	  equations_add=compartment_and_equations.equation_names_add;
	  equations_subtract=compartment_and_equations.equation_names_subtract;

	  adding=is_in_vector(equations_add, equation_name);
	  subtracting=is_in_vector(equations_subtract, equation_name);

	  if(adding or subtracting)
	    {
	      result=compartment;
	    }
	}
      begin++;
    }
  return result;
}

vector<string> check_equations(const vector<string> equation_names, const string compartment_name)
{
  const int size=equation_names.size();
  string compartment;
  vector<string> compartment_list;

  if(size>0)
    {
      for(const auto&i: equation_names)
	{
	  compartment=find_compartment(i, compartment_name);
	  compartment_list.push_back(compartment);
	}
    }
  return compartment_list;
}

void target_compartments(const string compartment_name)
{
  string compartment;
  vector<string> equation_names_add;
  vector<string> equation_names_subtract;
  vector<string> adding_to_compartments;
  vector<string> subtracting_to_compartments;
  EquationNamesAddSubtract compartment_and_equations;
  map<string, EquationNamesAddSubtract>::iterator begin=compartments_and_equations.begin();
  map<string, EquationNamesAddSubtract>::iterator end=compartments_and_equations.end();
  TargetCompartments target_compartments_i;

  while(begin!=end)
    {
      compartment=begin->first;

      compartment_and_equations=compartments_and_equations[compartment];
      equation_names_add=compartment_and_equations.equation_names_add;
      equation_names_subtract=compartment_and_equations.equation_names_subtract;

      if(compartment==compartment_name)
	{
	  adding_to_compartments=check_equations(equation_names_add, compartment_name);
	  subtracting_to_compartments=check_equations(equation_names_subtract, compartment_name);
	  target_compartments_i.add_to_compartments=subtracting_to_compartments;
	  target_compartments_i.subtract_from_compartments=adding_to_compartments;
	  compartment_target_map[compartment_name]=target_compartments_i;
	}
      begin++;
    }
}

void create_target_compartment_map()
{
  for(const auto&i: compartment_diagonal)
    {
      target_compartments(i);
    }
}
