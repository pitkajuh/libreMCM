/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "../global/global.h"
#include "../class/EquationsParseData.h"
#include "../class/EquationsIndices.h"
#include "../class/EquationsIndicesAll.h"
#include "../wdata/values_to_graph.h"
#include "../rcompartment/read_compartment_definition.h"
#include "../map/create_maps.h"

using std::map;

vector<int> indices_update(vector<int> indices, int nr)
{
  int i=0;
  int indice;

  while(i<=indices.size()-1)
    {
      indice=indices[i];
      indices[i]=indice+nr;
      i++;
    }
  return indices;
}

vector<string> combine_string_vectors_equation(vector<string> combine1, vector<string> combine2)
{
  int i=0;
  int size=combine2.size();
  string combine2_i;

  while(i<=size-1)
    {
      combine2_i=combine2[i];
      combine1.push_back(combine2_i);
      i++;
    }
  return combine1;
}

vector<string> combine_string_vectors(vector<string> combine1, vector<string> combine2)
{
  int i=0;
  int size=combine2.size();
  string combine2_i;

  while(i<=size-1)
    {
      combine2_i=combine2[i];
      combine1.push_back(combine2_i);
      i++;
    }
  return combine1;
}

vector<int> combine_int_vectors(vector<int> combine1, vector<int> combine2)
{
  int i=0;
  int combine2_i;

  while(i<=combine2.size()-1)
    {
      combine2_i=combine2[i];
      combine1.push_back(combine2_i);
      i++;
    }
  return combine1;
}

vector<string> equation_subtract(vector<string> fa)
{
  int i=0;
  int size=fa.size();
  int ip1;
  string fchar;
  string fchar_ip1;
  const int zero_value=0;

  while(i<=size-1)
    {
      fchar=fa[i];
      fchar_ip1=fchar[0];

      if(i==0)
	{
	  if(fchar_ip1==subtract)
	    {
	      fchar.erase(fchar.begin()+zero_value);
	      fa[i]=fchar;
	    }
	  else
	    {
	      fa[i]=subtract+fchar;
	    }
	}

      if(fchar_ip1==subtract and i>0)
	{
	  fchar.erase(fchar.begin()+zero_value);
	  fa[i]=fchar;
	}
      i++;
    }
  return fa;
}

EquationsIndicesSub combine_equations_and_indices_subroutine(EquationsParseData vector1, string wanted_parameter)
{
  int i=0;
  int size=vector1.get_size();
  int indice_found_at;
  int indice_add;
  bool add_or_not;
  bool indice_found=false;
  vector<string> equation;
  vector<string> final_eq;
  vector<string> parameter_data_for_indices;
  vector<string> parameter_data_for_indices_final;
  vector<int> indices;
  vector<int> indices_final;
  EquationParseData vector1_i;
  string parameter_data_for_indices_first_elem;
  EquationsIndicesSub rt;
  const int begin=0;

  while(i<=size-1)
    {
      vector1_i=vector1.get(i);
      equation=vector1_i.equation;
      indices=vector1_i.indices;
      add_or_not=vector1_i.add_equation;
      parameter_data_for_indices=vector1_i.compartments;
      parameter_data_for_indices_first_elem=parameter_data_for_indices[begin];

      if(parameter_data_for_indices_first_elem==wanted_parameter)
	{
	  if(!indice_found)
	    {
	      indice_found_at=i;
	      indice_found=true;
	    }

	  if(add_or_not)
	    {
	      if(i==0)
		{
		  final_eq=combine_string_vectors_equation(final_eq, equation);
		  indices_final=indices;
		  parameter_data_for_indices_final=parameter_data_for_indices;
		}
	      else
		{
		  equation.insert(equation.begin()+begin, add);
		  indice_add=1+final_eq.size();
		  indices=indices_update(indices, indice_add);
		  indices_final=combine_int_vectors(indices_final, indices);
		  parameter_data_for_indices_final=combine_string_vectors(parameter_data_for_indices_final, parameter_data_for_indices);
		  final_eq=combine_string_vectors_equation(final_eq, equation);
		}
	    }
	  else
	    {
	      equation=equation_subtract(equation);
	      equation.insert(equation.begin()+begin, add);
	      indice_add=1+final_eq.size();
	      indices=indices_update(indices, indice_add);
	      indices_final=combine_int_vectors(indices_final, indices);
	      parameter_data_for_indices_final=combine_string_vectors(parameter_data_for_indices_final, parameter_data_for_indices);
	      final_eq=combine_string_vectors_equation(final_eq, equation);
	    }
	}
      i++;
    }
  rt.equation=final_eq;
  rt.indices=indices_final;
  rt.parameter_data=parameter_data_for_indices_final;
  rt.in_indice=indice_found_at;
  return rt;
}

EquationsIndicesAll combine_equations_and_indices(EquationsParseData vector1, string compartment_name)
{
  int i_start;
  EquationsIndicesSub equation_data;
  EquationsIndicesAll rt;
  EquationsIndices rt_i;
  vector<string> equation_data_0;
  vector<int> equation_data_1;
  vector<string> equation_data_2;
  map<string, vector<string>> parameter_data_1=compartment_map[compartment_name];
  map<string, vector<string>> parameter_map_i;
  map<string, vector<string>>::iterator parameter_map_begin=parameter_data_1.begin();
  map<string, vector<string>>::iterator parameter_map_end=parameter_data_1.end();
  string parameter_name;

  while(parameter_map_begin!=parameter_map_end)
    {
      parameter_name=parameter_map_begin->first;
      parameter_name=compartment_name+parm_delim+parameter_name;
      equation_data=combine_equations_and_indices_subroutine(vector1, parameter_name);
      equation_data_0=equation_data.equation;
      equation_data_1=equation_data.indices;
      equation_data_2=equation_data.parameter_data;

      rt_i.equation=equation_data_0;
      rt_i.indices=equation_data_1;
      rt_i.parameter_data=equation_data_2;
      rt.push_back(rt_i);
      i_start=equation_data.in_indice;
      vector1.erase(i_start);
      parameter_map_begin++;
    }
  return rt;
}
