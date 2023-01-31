/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <vector>
#include "../global/global.h"

using namespace std;

vector<vector<string>> comp_vector;

vector<string> line_read(string line)
{
  int i;
  string ab;
  const string empty_str_const="";
  const string str_bug1="\357";
  const string str_bug2="\273";
  const string str_bug3="\277";
  string empty_str=empty_str_const;
  string fchar;
  vector<string> empty;

  while(i<=line.size()-1)
    {
      fchar=line[i];

      if(fchar==delimiter)
	{
	  empty.push_back(empty_str);
	  empty_str=empty_str_const;
	}
      else
	{
	  if(fchar==str_bug1 or fchar==str_bug2 or fchar==str_bug3)
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
  vector<vector<string>> compartment_vector;
  vector<string> line_read_i;

  while(getline(csv_loaded, line))
    {
      line_read_i=line_read(line);
      compartment_vector.push_back(line_read_i);
    }

  return compartment_vector;
}

void get_compartment_vector(string directory)
{
  string csv=directory+"compartment.csv";
  comp_vector=read_compartment(csv);
}
