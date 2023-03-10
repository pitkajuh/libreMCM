/*--------------------------------*- C++ -*----------------------------------* \
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "read_compartment_definition.h"
#include "read_compartment.h"
#include "../class/CompartmentEquationsAddSubtract.h"
#include "../class/EquationNamesAddSubtract.h"
#include "../global/global.h"
#include "../util/is_in_vector.h"
#include "../rcfg/read_bin.h"

map<string, EquationNamesAddSubtract> compartments_and_equations;

vector<string> get_eq_corresponding_to_eq_name(string eq_name)
{
  // Takes equation name as an input (for example f) and returns its value (for example f=x^2+y^2)
  vector<string> rt=equations_map[eq_name];
  bool is_empty=rt.empty();

  if(is_empty)
    {
      rt={not_found};
    }
  return rt;
}

Equations get_equation_values(vector<string> equation_names)
{
  // Takes equation names as an input and returns their values in a vector.
  int i=0;
  string equation_name;
  vector<string> equation_value;
  Equations equation_values;

  if(equation_names.size()>0)
    {
      while(i<=equation_names.size()-1)
	{
	  equation_name=equation_names[i];
	  equation_value=get_eq_corresponding_to_eq_name(equation_name);
	  equation_values.push_back(equation_value);
	  i++;
	}
    }
  return equation_values;
}

vector<string> get_equations_from_compartment_map(string compartment, map<int, vector<string>> compartment_map)
{
  int i=0;
  int compartment_index;
  string compartment_vector_i;
  string compartment_vector_c;
  bool is_str_compartment;
  bool is_empty;
  vector<string> compartment_vector;
  vector<string> rt;
  IsInVector is_str_compartment_i;
  map<int, vector<string>>::iterator begin=compartment_map.begin();
  map<int, vector<string>>::iterator end=compartment_map.end();

  while(begin!=end)
    {
      compartment_index=begin->first;
      compartment_vector=compartment_map[compartment_index];
      is_str_compartment_i=is_in_vector(compartment_vector, compartment);
      is_str_compartment=is_str_compartment_i.is_in_vector;

      if(is_str_compartment)
	{
	  while(i<=compartment_vector.size()-1)
	    {
	      compartment_vector_i=compartment_vector[i];
	      is_str_compartment_i=is_in_vector_compartment(compartment_diagonal, compartment_vector_i);
	      is_str_compartment=is_str_compartment_i.is_in_vector;
	      is_empty=compartment_vector_i.empty();

	      if(!is_empty and !is_str_compartment)
		{
		  rt.push_back(compartment_vector_i);
		}
	      i++;
	    }
	}
      is_str_compartment=false;
      i=0;
      begin++;
    }
  return rt;
}

CompartmentEquationsAddSubtract get_equations_compartment(string compartment)
{
  vector<string> equations_names_subtract=get_equations_from_compartment_map(compartment, row_map);
  Equations equations_subtract=get_equation_values(equations_names_subtract);

  vector<string> equations_names_add=get_equations_from_compartment_map(compartment, column_map);
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
