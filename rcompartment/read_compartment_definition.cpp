/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <fstream>
#include "read_compartment.h"
#include "get_parameter_value.h"
#include "../class/InitialValuesHalfLife.h"
#include "../class/AllCompartmentInitialValuesHalfLife.h"
#include "../class/AllInitialValuesHalfLife.h"
#include "../class/NoCompartmentInitialValuesHalfLife.h"
#include "../class/CompartmentAllInitialValuesHalfLife.h"
#include "../class/AllCompartmentAllInitialValuesHalfLife.h"
#include "../global/global.h"
#include "../rcfg/read_constants.h"
#include "../util/remove_white_space.h"
#include "../util/line_remove_comment.h"
#include "../wdata/values_to_graph.h"

using std::fstream;
using std::ios_base;
using std::ios;

AllCompartmentAllInitialValuesHalfLife compartment_parameters_rt;
AllCompartmentAllInitialValuesHalfLife compartment_parameters;

InitialValuesHalfLife read_compartment_element(string elem, string compartment_name)
{
  int i=0;
  float half_life;
  string empty;
  string name;
  string fchar;
  string value;
  InitialValueHalfLife result;
  InitialValuesHalfLife rt;

  while(i<=elem.size()-1)
    {
      fchar=elem[i];

      if(fchar==equal_sign)
	{
	  name=compartment_name+parm_delim+empty;
	  empty="";
	}
      else if(fchar==delimiter)
	{
	  value=empty;
	  // get half life if is radionuclide
	  result.initial_value_name=name;
	  result.initial_value=value;
	  result.half_life=half_life;
	  rt.push_back(result);
	  empty="";
	}
      else
	{
	  empty=empty+fchar;
	}
      i++;
    }
  return rt;
}

void read_compartment_def(string directory)
{
  const string file_name=directory+"compartments";
  const string compartments_str="compartments";
  const string materials="content";
  string line;
  string line_a;
  string first_char;
  string compartment_name;
  string compartment_c;
  string line_commented;
  string line_substr;
  bool compartments_found=false;
  bool compartments_saved=false;
  bool compartment_name_found=false;
  bool materials_found=false;
  bool line_is_empty;
  bool line_commented_is_empty;
  fstream bin_loaded(file_name, ios_base::in | ios::binary);
  InitialValuesHalfLife compartment_i;
  AllInitialValuesHalfLife compartments_values;
  CompartmentAllInitialValuesHalfLife compartment_parameters_i;

  while(getline(bin_loaded, line))
    {
      line_commented=line_remove_comment(line);
      line_is_empty=line.empty();
      line_commented_is_empty=line_commented.empty();

      if(line_is_empty or line_commented_is_empty)
	{
	  continue;
	}
      else if(!compartments_saved)
	{
	  if(line==curly_bracket_c and compartments_found)
	    {
	      compartments_saved=true;
	      continue;
	    }
	  else if(line==compartments_str or line==compartments_str+curly_bracket_o)
	    {
	      compartments_found=true;
	      continue;
	    }
	  else if(compartments_found)
	    {
	      line_a=remove_white_space(line);
	      first_char=line_a[line_a.size()-1];
	      line_substr=line_a.substr(0, line_a.size()-1);

	      if(first_char==curly_bracket_o and line_substr!=materials)
		{
		  compartment_name=line_a.substr(0, line_a.size()-1);
		  compartment_name_found=true;
		}
	      else if(compartment_name_found)
		{
		  if(line_a==materials or line_a==materials+curly_bracket_o)
		    {
		      materials_found=true;
		    }
		  else if(materials_found and line_a!=curly_bracket_c)
		    {
		      compartment_i=read_compartment_element(line_a, compartment_name);
		      compartments_values.push_back(compartment_i);
		    }
		  else if(line_a==curly_bracket_c)
		    {
		      compartment_parameters_i.compartment=compartment_name;
		      compartment_parameters_i.initial_values=compartments_values;
		      compartment_parameters.push_back(compartment_parameters_i);
		      compartments_values.clear();
		      compartment_name_found=false;
		      materials_found=false;
		    }
		}
	    }
	}
    }
  compartment_parameters_rt=compartment_parameters;
}
