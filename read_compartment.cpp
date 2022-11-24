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
#include <vector>
#include "global.h"

using namespace std;

vector<string> line_read(string line)
{
  int i; // index
  string ab, empty_str="", fchar; // empty strings used for appending
  vector<string> empty; // empty vector for appending

  while(i<=line.size()-1)
    {
      fchar=line[i];

      if(fchar==delimiter)
	{
	  empty.push_back(empty_str);
	  empty_str="";
	}
      else
	{
	  if(fchar=="\357" or fchar=="\273" or fchar=="\277")
	    {
	      i++;
	      continue;
	    }
	  else{
	    empty_str=empty_str+fchar;
	  }
	}
      i++;
    }

  empty.push_back(empty_str);

  return empty;
}

vector<vector<string>> read_compartment(string csv)
{
  string line;
  fstream csv_loaded(csv, ios_base::in | ios::binary);
  int aa;
  vector<vector<string>> compartment_vector;

  while(getline(csv_loaded, line))
    {
      compartment_vector.push_back(line_read(line));
    }

  return compartment_vector;
}

vector<vector<string>> get_compartment_vector()
{
  string csv="cfg/compartment.csv";
  vector<vector<string>> read=read_compartment(csv);

  return read;
}
