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
#include "../global/t_end.h"
#include "../global/global_constants.h"
#include "../global/all_parameters.h"
#include "../global/compartments_and_equations_map.h"
#include "../global/compartment_diagonal.h"
#include "../global/compartment_diagonal_v2.h"
#include "../global/compartment_parameters.h"
#include "../global/compartment_map_v2.h"
#include "../global/compartment_map.h"
#include "../global/all_values.h"
#include "../global/initial_value_map.h"
#include "../global/compartment_target_map.h"
#include "../global/parameter_map.h"
#include "../global/equations_map.h"
#include "../global/row_map.h"
#include "../global/column_map.h"
#include "../global/initial_values_all.h"
#include "../global/h.h"
#include "../global/probabilistic.h"

using std::ofstream;
using std::to_string;

void write_to_file(const string directory, const int run_no)
{
  int i=0;
  int j=0;
  int k=0;
  int size;
  int value_vector_size;
  double t=0;
  const string str_new_row="\n";
  const string file_type=".txt";
  const string header_const="t"+DELIMITER;
  string header=header_const;
  string line="";
  string t_str;
  string save_path;
  string compartment_name;
  string initial_value_name;
  string value;
  string run_no_str;
  bool ready=false;
  vector<string> initial_value_names;
  vector<string> value_vector;
  map<string, map<string, vector<string>>>::reverse_iterator begin=compartment_map.rbegin();
  map<string, map<string, vector<string>>>::reverse_iterator end=compartment_map.rend();
  map<string, vector<string>> values;

  while(begin!=end)
    {
      compartment_name=begin->first;

      if(probabilistic)
	{
	  run_no_str=to_string(run_no);
	  save_path=directory+compartment_name+run_no_str+file_type;
	}
      else
	{
	  save_path=directory+compartment_name+file_type;
	}
      ofstream myfile(save_path);
      initial_value_names=compartment_map_v2[compartment_name];
      values=compartment_map[compartment_name];
      size=initial_value_names.size()-1;

      // Create header line containing initial value names (t;iv1;iv2;iv3...)
      while(i<=size)
	{
	  initial_value_name=initial_value_names[i];

	  if(size==0)
	    {
	      header=header+initial_value_name+str_new_row;
	    }
	  else if(i==size)
	    {
	      header=header+initial_value_name+str_new_row;
	    }
	  else
	    {
	      header=header+initial_value_name+DELIMITER;
	    }
	  i++;
	}

      while(not ready)
	{
	  initial_value_name=initial_value_names[j];
	  value_vector=values[initial_value_name];
	  value=value_vector[k];
	  size=initial_value_names.size()-1;
	  if(size==0)
	    {
	      // Write result when there are only one initial value in each compartment.
	      value_vector_size=value_vector.size()-1;

	      if(j==size and k==value_vector_size)
		{
		  ready=true;
		  break;
		}
	      else if(k<=value_vector_size)
		{
		  t_str=to_string(t);
		  line=line+t_str+DELIMITER+value+str_new_row;
		  t=t+h;
		  k++;
		  continue;
		}
	    }
	  else
	    {
	      // Write result when there are more than one initial value in each compartment.
	      size=initial_value_names.size()-1;
	      value_vector_size=value_vector.size()-1;

	      if(k==value_vector_size and j==size)
		{
		  line=line+DELIMITER+value;
		  ready=true;
		}
	      else if(j<=size)
		{
		  if(j==0)
		    {
		      t_str=to_string(t);
		      line=line+t_str+DELIMITER+value;
		    }
		  else if(j==size)
		    {
		      line=line+DELIMITER+value+str_new_row;
		      k++;
		      t=t+h;
		      j=0;
		      continue;
		    }
		  else
		    {
		      line=line+DELIMITER+value;
		    }
		}
	    }
	  j++;
	}
      // Write header and results to file
      myfile<<header;
      myfile<<line;
      myfile.close();
      ready=false;
      i=0;
      j=0;
      k=0;
      t=0;
      line="";
      header=header_const;
      begin++;
    }
}
