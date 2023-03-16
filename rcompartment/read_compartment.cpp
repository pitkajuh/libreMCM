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
#include <map>
#include "../global/global.h"
#include "../debug/debug.h"

using std::map;
using std::fstream;
using std::ios_base;
using std::ios;

vector<string> compartment_diagonal; // Contains void and origin.
vector<string> compartment_diagonal_v2; // Does not contain void or origin.
map<int, vector<string>> row_map;
map<int, vector<string>> column_map;
bool create_column_numbers=true;

vector<string> line_read(string line)
{
  // Takes the line from .csv file as an input (as a string) and converts it to veector form based on the chosen delimiter of the .csv file (; is the default delimiter).
  int i;
  const int size=line.size();
  const string str_bug1="\357";
  const string str_bug2="\273";
  const string str_bug3="\277";
  string empty_str="";
  string fchar;
  vector<string> empty;

  while(i<=size-1)
    {
      fchar=line[i];

      if(fchar==DELIMITER)
	{
	  empty.push_back(empty_str);
	  empty_str="";
	}
      else
	{
	  if(fchar==str_bug1 or fchar==str_bug2 or fchar==str_bug3)
	    {
	      i++;
	      continue;
	    }
	  else
	    {
	      empty_str=empty_str+fchar;
	    }
	}
      i++;
    }
  empty.push_back(empty_str);
  return empty;
}

void create_column(vector<string> row)
{
  // Takes compartment row from .csv file as input and converts it to column.
  int i=0;
  const int size=row.size();
  string row_i;
  vector<string> column_vector;

  while(i<=size-1)
    {
      row_i=row[i];

      if(create_column_numbers)
	{
	  column_vector.push_back(row_i);
	  column_map[i]=column_vector;
	  column_vector.clear();
	}
      else
	{
	  column_vector=column_map[i];
	  column_vector.push_back(row_i);
	  column_map[i]=column_vector;
	}
      i++;
    }
  create_column_numbers=false;
}

void read_compartments(string csv)
{
  // Reads compartments .csv file line by line and creates row and column maps.
  int line_nr=0;
  string line;
  string diagonal_compartment;
  fstream csv_loaded(csv, ios_base::in | ios::binary);
  vector<vector<string>> compartment_vector;
  vector<string> line_read_i;

  while(getline(csv_loaded, line))
    {
      line_read_i=line_read(line);
      diagonal_compartment=line_read_i[line_nr];

      compartment_diagonal.push_back(diagonal_compartment);

      if(diagonal_compartment!=VOID and diagonal_compartment!=ORIGIN)
	{
	  compartment_diagonal_v2.push_back(diagonal_compartment);
	}
      row_map[line_nr]=line_read_i;
      create_column(line_read_i);
      line_nr++;
    }
}

void get_compartments(string directory)
{
  string csv=directory+"compartment.csv";
  read_compartments(csv);
}
