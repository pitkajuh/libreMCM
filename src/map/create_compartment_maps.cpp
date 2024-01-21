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
#include "../global/global_constants.h"
#include "../global/parameter_map.h"
#include "../global/compartment_map_v2.h"
#include "../global/compartment_map.h"
#include "../global/compartment_map_orig.h"
#include "../global/compartment_target_map.h"
#include "../global/global_constants.h"
#include "../global/initial_values_all.h"
#include "../global/all_parameters.h"
#include "../global/compartment_diagonal.h"
#include "../global/compartment_diagonal_v2.h"
#include "../util/is_in_vector.h"

void create_compartment_map()
{
  int i=0;
  int j=0;
  int k=0;
  int l=0;
  int l1=0;
  int compartment_nr=0;
  int initial_values_all_j_size;
  const int size=compartment_diagonal.size();
  const int compartment_diagonal_v2_size=compartment_diagonal_v2.size();
  const int initial_values_all_size=initial_values_all.size();
  const int all_parameters_size=all_parameters.size();
  bool is_void;
  bool is_origin;
  bool not_found=false;
  string compartment_name;
  string parameter_with_i_value;
  string parameter_initial_value;
  string parameter;
  string compartment;
  InitialValues initial_values_all_j;
  InitialValue initial_value;
  TargetCompartments target_compartments;
  vector<string> parameter_values_vector;
  vector<string> compartment_adding;
  vector<string> compartment_subtracting;
  vector<string> compartment_map_v2_vec;

  sort(all_parameters.begin(), all_parameters.end());

  while(compartment_nr<=size-1)
    {
      compartment=compartment_diagonal[compartment_nr];

      while(i<=compartment_diagonal_v2_size-1)
	{
	  compartment_name=compartment_diagonal_v2[i];

	  if(compartment==compartment_name)
	    {
	      target_compartments=compartment_target_map[compartment];
	      compartment_adding=target_compartments.subtract_from_compartments;
	      compartment_subtracting=target_compartments.add_to_compartments;

	      is_void=is_in_vector(compartment_subtracting, VOID);
	      is_origin=is_in_vector(compartment_adding, ORIGIN);

	      while(j<=initial_values_all_size-1)
		{
		  initial_values_all_j=initial_values_all[j];
		  initial_values_all_j_size=initial_values_all_j.size();

		  while(k<=initial_values_all_j_size-1)
		    {
		      initial_value=initial_values_all_j[k];
		      parameter_with_i_value=initial_value.initial_value_name;
		      parameter_initial_value=initial_value.initial_value;

		      while(l<=all_parameters_size-1)
			{
			  parameter=all_parameters[l];

			  if(parameter==parameter_with_i_value)
			    {
			      parameter_values_vector.push_back(parameter_initial_value);
			      parameter_map[parameter_with_i_value]=parameter_values_vector;
			      parameter_values_vector.clear();
			      compartment_map_v2_vec.push_back(parameter_with_i_value);
			      initial_values_all_j_size=initial_values_all_j.size();
			      l++;

			      if(k==initial_values_all_j_size-1 and l<=all_parameters_size-1)
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
			      parameter_values_vector.push_back(ZERO);
			      parameter_map[parameter]=parameter_values_vector;
			      parameter_values_vector.clear();
			      compartment_map_v2_vec.push_back(parameter);
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
	  else if(i==compartment_diagonal_v2_size-1)
	    {
	      not_found=true;
	      i++;
	      continue;
	    }
	  i++;
	}
      if(not_found)
	{
	  if(compartment!=VOID and compartment!=ORIGIN)
	    {
	      while(l1<=all_parameters_size-1)
		{
		  parameter=all_parameters[l1];
		  parameter_values_vector.push_back(ZERO);
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
  compartment_map_orig=compartment_map;
}
