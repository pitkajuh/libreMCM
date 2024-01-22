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

const string NEW_ROW="\n";
const string HEADER_CONST="t"+DELIMITER;

const string create_save_path(const string directory, const string compartment_name, const int run_no)
{
  const string file_type=".txt";

  if(probabilistic){return directory+compartment_name+to_string(run_no)+file_type;}
  else{return directory+compartment_name+file_type;}
}

const string create_header(const vector<string> initial_value_names)
{
  // Create header line containing initial value names (t;iv1;iv2;iv3...)
  int i=0;
  const int size=initial_value_names.size()-1;
  string initial_value_name;
  string header=HEADER_CONST;

  while(i<=size)
    {
      initial_value_name=initial_value_names[i];

      if(size==0 or i==size){header+=initial_value_name+NEW_ROW;}
      else{header+=initial_value_name+DELIMITER;}
      i++;
    }
  return header;
}

void write_to_file(const string directory, const int run_no)
{
  int i=0;
  int j=0;
  int k=0;
  int size;
  int value_vector_size;
  bool ready=false;
  double t=0;
  string header;
  string line="";
  string t_str;
  string compartment_name;
  string initial_value_name;
  string value;
  string save_path;
  vector<string> initial_value_names;
  vector<string> value_vector;
  unordered_map<string, vector<string>> values;

  for(auto n=compartment_map.begin(); n!=compartment_map.end(); n++)
    {
      compartment_name=n->first;
      save_path=create_save_path(directory, compartment_name, run_no);
      ofstream file_save(save_path);
      initial_value_names=compartment_map_v2[compartment_name];
      values=compartment_map[compartment_name];
      header=create_header(initial_value_names);

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
		  line+=t_str+DELIMITER+value+NEW_ROW;
		  t+=h;
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
		  line+=DELIMITER+value;
		  ready=true;
		}
	      else if(j<=size)
		{
		  if(j==0)
		    {
		      t_str=to_string(t);
		      line+=t_str+DELIMITER+value;
		    }
		  else if(j==size)
		    {
		      line+=DELIMITER+value+NEW_ROW;
		      k++;
		      t+=h;
		      j=0;
		      continue;
		    }
		  else{line+=DELIMITER+value;}
		}
	    }
	  j++;
	}
      // Write header and results to file
      file_save<<header;
      file_save<<line;
      file_save.close();
      ready=false;
      i=0;
      j=0;
      k=0;
      t=0;
      line="";
      header=HEADER_CONST;
    }
}
