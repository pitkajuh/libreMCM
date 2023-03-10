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
#include <map>
#include "../class/TargetCompartments.h"
#include "../global/global.h"
#include "../rcompartment/read_compartment.h"
#include "../rcompartment/get_compartment_equations.h"
#include "../wdata/values_to_graph.h"
#include "../util/is_in_vector.h"

using std::map;

map<string, vector<string>> parameter_map;
map<string, vector<string>> compartment_map_v2;
map<string, map<string, vector<string>>> compartment_map;
map<string, TargetCompartments> compartment_target_map;

string find_compartment(string equation_name, string compartment_name)
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
  IsInVector in_vector_add;
  IsInVector in_vector_subtract;

  while(begin!=end)
    {
      compartment=begin->first;

      if(compartment_name!=compartment)
	{
	  compartment_and_equations=compartments_and_equations[compartment];
	  equations_add=compartment_and_equations.equation_names_add;
	  equations_subtract=compartment_and_equations.equation_names_subtract;

	  in_vector_add=is_in_vector(equations_add, equation_name);
	  in_vector_subtract=is_in_vector(equations_subtract, equation_name);

	  adding=in_vector_add.is_in_vector;
	  subtracting=in_vector_subtract.is_in_vector;

	  if(adding or subtracting)
	    {
	      result=compartment;
	    }
	}
      begin++;
    }
  return result;
}

vector<string> check_equations(vector<string> equation_names, string compartment_name)
{
  int i=0;
  int size=equation_names.size();
  string equation_name;
  string compartment;
  vector<string> compartment_list;

  if(size>0)
    {
      while(i<=size-1)
	{
	  equation_name=equation_names[i];
	  compartment=find_compartment(equation_name, compartment_name);
	  compartment_list.push_back(compartment);
	  i++;
	}
    }
  return compartment_list;
}

void target_compartments(string compartment_name)
{
  string compartment;
  vector<string> equation_names_add;
  vector<string> equation_names_subtract;
  EquationNamesAddSubtract compartment_and_equations;
  vector<string> adding_to_compartments;
  vector<string> subtracting_to_compartments;
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
  int i=0;
  int size=compartment_diagonal.size();
  string compartment;

  while(i<=size-1)
    {
      compartment=compartment_diagonal[i];
      target_compartments(compartment);
      i++;
    }
}

void create_compartment_map()
{
  int i=0;
  int j=0;
  int k=0;
  int l=0;
  int l1=0;
  int compartment_nr=0;
  int size=compartment_diagonal.size();
  int all_compartments_size=all_compartments.size();
  int initial_values_all_size=initial_values_all.get_size();
  int initial_values_all_j_size;
  string compartment_name;
  string parameter_with_i_value;
  string parameter_initial_value;
  string parameter;
  string compartment;
  const string zero_value="0";
  InitialValues initial_values_all_j;
  InitialValue initial_value;
  TargetCompartments target_compartments;
  vector<string> parameter_values_vector;
  vector<string> compartment_adding;
  vector<string> compartment_subtracting;
  vector<string> compartment_map_v2_vec;
  IsInVector is_void_i;
  IsInVector is_origin_i;
  bool is_void;
  bool is_origin;
  bool not_found=false;

  sort(all_parameters.begin(), all_parameters.end());
  create_target_compartment_map();

  while(compartment_nr<=size-1)
    {
      compartment=compartment_diagonal[compartment_nr];

      while(i<=all_compartments_size-1)
	{
	  compartment_name=all_compartments[i];

	  if(compartment==compartment_name)
	    {
	      target_compartments=compartment_target_map[compartment];
	      compartment_adding=target_compartments.subtract_from_compartments;
	      compartment_subtracting=target_compartments.add_to_compartments;

	      is_void_i=is_in_vector_compartment(compartment_subtracting, void_element);
	      is_origin_i=is_in_vector_compartment(compartment_adding, origin_element);

	      is_void=is_void_i.is_in_vector;
	      is_origin=is_origin_i.is_in_vector;

	      while(j<=initial_values_all_size-1)
		{
		  initial_values_all_j=initial_values_all.get(j);
		  initial_values_all_j_size=initial_values_all_j.get_size();

		  while(k<=initial_values_all_j_size-1)
		    {
		      initial_value=initial_values_all_j.get(k);
		      parameter_with_i_value=initial_value.initial_value_name;
		      parameter_initial_value=initial_value.initial_value;

		      while(l<=all_parameters.size()-1)
			{
			  parameter=all_parameters[l];

			  if(parameter==parameter_with_i_value)
			    {
			      parameter_values_vector.push_back(parameter_initial_value);
			      parameter_map[parameter_with_i_value]=parameter_values_vector;
			      parameter_values_vector.clear();
			      compartment_map_v2_vec.push_back(parameter_with_i_value);
			      initial_values_all_j_size=initial_values_all_j.get_size();
			      l++;

			      if(k==initial_values_all_j_size-1 and l<=all_parameters.size()-1)
				{
				  continue;
				}
			      else
				{
				  break;
				}
			    }
			  else if(!is_origin and !is_void)
			    {
			      parameter_values_vector.push_back(zero_value);
			      parameter_map[parameter]=parameter_values_vector;
			      parameter_values_vector.clear();
			    }
			  l++;
			}
		      k++;
		    }

		  compartment_map_v2[compartment]=compartment_map_v2_vec;
		  compartment_map_v2_vec.clear();

		  l=0;
		  k=0;
		  j++;
		  i++;
		  not_found=false;
		  break;
		}
	      compartment_map[compartment]=parameter_map;
	      parameter_map.clear();
	    }
	  else if(i==all_compartments_size-1)
	    {
	      not_found=true;
	      i++;
	      continue;
	    }
	  i++;
	}
      if(not_found)
	{
	  if(compartment!=void_element and compartment!=origin_element)
	    {
	      while(l1<=all_parameters.size()-1)
		{
		  parameter=all_parameters[l1];
		  parameter_values_vector.push_back(zero_value);
		  parameter_map[parameter]=parameter_values_vector;
		  parameter_values_vector.clear();
		  l1++;
		}
	      l1=0;
	      compartment_map[compartment]=parameter_map;
	      parameter_map.clear();
	      not_found=false;
	    }
	}
      i=0;
      compartment_nr++;
    }
}
