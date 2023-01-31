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
#include <vector>
#include "../global/global.h"
#include "../rcompartment/read_compartment_definition.h"

using namespace std;

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

vector<string> combine_string_vectors(vector<string> combine1, vector<string> combine2)
{
  int i=0;
  string combine2_i;

  while(i<=combine2.size()-1)
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
  int ip1;
  string fchar;
  string fchar_ip1;
  const int zero_value=0;

  while(i<=fa.size()-1)
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

tuple<vector<string>, vector<int>, vector<string>, int>
combine_equations_and_indices_subroutine(vector<tuple<vector<string>, vector<int>, bool, vector<string>>> vector1, string wanted_parameter)
{
  int i=0;
  int indice_found_at;
  vector<string> equation;
  vector<string> final_eq;
  vector<string> parameter_data_for_indices;
  vector<string> parameter_data_for_indices_final;
  vector<int> indices;
  vector<int> indices_final;
  bool add_or_not;
  bool indice_found=false;
  tuple<vector<string>, vector<int>, bool, vector<string>> vector1_i;
  string parameter_data_for_indices_first_elem;
  tuple<vector<string>, vector<int>, vector<string>, int> rt;
  int indice_add;

  while(i<=vector1.size()-1)
    {
      vector1_i=vector1[i];
      parameter_data_for_indices=get<3>(vector1_i);
      equation=get<0>(vector1_i);
      indices=get<1>(vector1_i);
      add_or_not=get<2>(vector1_i);
      parameter_data_for_indices_first_elem=parameter_data_for_indices[0];

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
		  final_eq=combine_string_vectors(final_eq, equation);
		  indices_final=indices;
		  parameter_data_for_indices_final=parameter_data_for_indices;
		}
	      else
		{
		  equation.insert(equation.begin(), add);
		  indice_add=1+final_eq.size();
		  indices=indices_update(indices, indice_add);
		  indices_final=combine_int_vectors(indices_final, indices);
		  parameter_data_for_indices_final=combine_string_vectors(parameter_data_for_indices_final, parameter_data_for_indices);
		  final_eq=combine_string_vectors(final_eq, equation);
		}
	    }
	  else
	    {
	      equation=equation_subtract(equation);
	      equation.insert(equation.begin(), add);
	      indice_add=1+final_eq.size();
	      indices=indices_update(indices, indice_add);
	      indices_final=combine_int_vectors(indices_final, indices);
	      parameter_data_for_indices_final=combine_string_vectors(parameter_data_for_indices_final, parameter_data_for_indices);
	      final_eq=combine_string_vectors(final_eq, equation);
	    }
	}
      i++;
    }

  rt=make_tuple(final_eq, indices_final, parameter_data_for_indices_final, indice_found_at);
  return rt;
}

vector<tuple<vector<string>, vector<int>, vector<string>>>
combine_equations_and_indices(vector<tuple<vector<string>, vector<int>, bool, vector<string>>> vector1, string compartment_name)
{
  int i=0;
  int j=0;
  int k=0;
  int half_life;
  int i_start;
  tuple<vector<string>, vector<int>, vector<string>, int> equation_data;
  string compartment_name_ch;
  string parameter_name;
  vector<vector<tuple<string, string, int>>> parameter_data_all;
  vector<tuple<string, string, int>> parameter_data;
  tuple<string, string, int> parameter_data_tuple;
  vector<tuple<vector<string>, vector<int>, vector<string>>> rt;
  tuple<vector<string>, vector<int>, vector<string>> rt_i;

  tuple<string, // compartment_name
	     vector<
	       vector<
		 tuple<
		   string, // parameter name
		   string, // parameter value
		   int // parameter half-life, is zero if parameter is not a radionuclide
		   >>
	       >
	     >
    compartment_parameters_i;
  vector<string>  equation_data_0;
  vector<int> equation_data_1;
  vector<string> equation_data_2;

  while(i<=compartment_parameters.size()-1)
    {
      compartment_parameters_i=compartment_parameters[i];
      compartment_name_ch=get<0>(compartment_parameters_i);

      if(compartment_name_ch==compartment_name)
	{
	  parameter_data_all=get<1>(compartment_parameters_i);

	  while(j<=parameter_data_all.size()-1)
	    {
	      parameter_data=parameter_data_all[j];

	      while(k<=parameter_data.size()-1)
		{
		  parameter_data_tuple=parameter_data[k];
		  parameter_name=get<0>(parameter_data_tuple);
		  equation_data=combine_equations_and_indices_subroutine(vector1, parameter_name);
		  equation_data_0=get<0>(equation_data);
		  equation_data_1=get<1>(equation_data);
		  equation_data_2=get<2>(equation_data);

		  rt_i=make_tuple(equation_data_0, equation_data_1, equation_data_2);
		  rt.push_back(rt_i);

		  i_start=get<3>(equation_data);
		  vector1.erase(vector1.begin()+i_start);
		  k++;
		}

	      k=0;
	      j++;
	    }
	}

      j=0;
      i++;
    }

  return rt;
}
