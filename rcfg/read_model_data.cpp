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
#include "read_config_sub.h"
#include "../global/global.h"

using namespace std;

string read_model_line(string line)
{
  int i=0;
  string result="";
  string fchar;

  while(i<=line.size()-1)
    {
      fchar=line[i];

      if(fchar!=delimiter)
	{
	  result=result+fchar;
	}
      i++;
    }
  return result;
}

vector<string> read_model_data()
{
  const string model_location="model_path";
  string model_data_file="./models_cfg";
  fstream model_loaded(model_data_file, ios_base::in | ios::binary);
  string line;
  string line_commented;
  bool model_found=false;
  bool model_saved=false;
  vector<string> models_vector;

  while(getline(model_loaded, line))
    {
      line=remove_white_space(line);
      line_commented=line_commented_or_not(line);

      if(line.empty() or line_commented.empty())
	{
	  continue;
	}
      else if(!model_saved)
	{
	  if(line==curly_bracket_c and model_found)
	    {
	      model_saved=true;
	      continue;
	    }
	  else if(line==model_location or line==model_location+curly_bracket_o)
	    {
	      model_found=true;
	      continue;
	    }
	  else if(model_found)
	    {
	      line=read_model_line(line);
	      models_vector.push_back(line);
	    }
	}
    }

  return models_vector;
}
