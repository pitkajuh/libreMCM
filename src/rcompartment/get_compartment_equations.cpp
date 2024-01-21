/*--------------------------------*- C++ -*----------------------------------* \
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <stdexcept>
#include "../global/compartment_diagonal.h"
#include "../global/equations_map.h"
#include "../global/row_map.h"
#include "../global/column_map.h"
#include "../global/compartments_and_equations_map.h"
#include "../global/equations_with_compartment_name.h"
#include "../class/CompartmentEquationsAddSubtract.h"
#include "../class/EquationNamesAddSubtract.h"
#include "../class/CompartmentEquationsAddSubtractAll.h"
#include "../util/is_in_vector.h"
#include "../util/combine_vectors.h"

vector<string> get_eq_corresponding_to_eq_name(const string eq_name)
{
  // Takes equation name as an input (for example f) and returns its value (for example f=x^2+y^2)
  vector<string> rt=equations_map[eq_name];
  bool is_empty=rt.empty();

  if(is_empty)
    {
      throw std::domain_error("ERROR! EQUATION "+eq_name+" WAS NOT FOUND!");
    }
  return rt;
}

Equations get_equation_values(const vector<string> equation_names)
{
  // Takes equation names as an input and returns their values in a vector.
  const int size=equation_names.size();
  vector<string> equation_value;
  Equations equation_values;

  if(size>0)
    {
      for(const auto&i: equation_names)
	{
	  equation_value=get_eq_corresponding_to_eq_name(i);
	  equation_values.push_back(equation_value);
	}
    }
  return equation_values;
}

vector<string> split_equation_names(const string names)
{
  // More than one transfer equation can act on a compartment. The equation names are writen on a same cell in csv-file and separated by comma (,). This function splits the equation names.
  int i=0;
  const int size=names.size()-1;
  string fchar;
  string empty="";
  const string comma=",";
  const string empty_value=" ";
  vector<string> rt;

  while(i<=size)
    {
      fchar=names[i];

      if(fchar!=empty_value)
	{
	  if(fchar==comma or i==size+1)
	    {
	      rt.push_back(empty);
	      empty="";
	    }
	  else
	    {
	      empty=empty+fchar;
	    }
	}
      i++;
    }
  rt.push_back(empty);
  return rt;
}

vector<string> get_equations_from_compartment_map(const string compartment, unordered_map<int, vector<string>> compartment_map)
{
  int compartment_index;
  bool is_compartment;
  bool is_empty;
  vector<string> compartment_vector;
  vector<string> rt;
  vector<string> names;

  for(auto i=compartment_map.begin(); i!=compartment_map.end(); i++)
    {
      compartment_index=i->first;
      compartment_vector=compartment_map[compartment_index];
      is_compartment=is_in_vector(compartment_vector, compartment);

      if(is_compartment)
	{
	  for(const auto&i: compartment_vector)
	    {
	      is_compartment=is_in_vector(compartment_diagonal, i);
	      is_empty=i.empty();

	      if(!is_empty and !is_compartment)
		{
		  names=split_equation_names(i);
		  rt=combine_vectors(names, rt);
		}
	    }
	}
      is_compartment=false;
    }
  return rt;
}

CompartmentEquationsAddSubtract get_equations_compartment(const string compartment)
{
  const vector<string> equations_names_subtract=get_equations_from_compartment_map(compartment, row_map);
  Equations equations_subtract=get_equation_values(equations_names_subtract);

  const vector<string> equations_names_add=get_equations_from_compartment_map(compartment, column_map);
  Equations equations_add=get_equation_values(equations_names_add);

  EquationNamesAddSubtract equations_add_subtract;
  equations_add_subtract.equation_names_add=equations_names_add;
  equations_add_subtract.equation_names_subtract=equations_names_subtract;
  compartments_and_equations[compartment]=equations_add_subtract;

  CompartmentEquationsAddSubtract rt;
  rt.compartment=compartment;
  rt.equations_add=equations_add;
  rt.equations_subtract=equations_subtract;

  return rt;
}

void get_compartment_equations()
{
  CompartmentEquationsAddSubtract equations;

  for(const auto&i: compartment_diagonal)
    {
      equations=get_equations_compartment(i);
      equations_with_compartment_name.push_back(equations);
    }
}
