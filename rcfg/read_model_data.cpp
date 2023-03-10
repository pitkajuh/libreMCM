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
#include "read_constants.h"
#include "../util/remove_white_space.h"
#include "../util/line_remove_comment.h"
#include "../global/global.h"

using std::fstream;
using std::ios_base;
using std::ios;

string read_model_line(string line)
{
  int i=0;
  int size=line.size();
  string result="";
  string fchar;

  while(i<=size-1)
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
  string line;
  string line_commented;
  fstream model_loaded(model_data_file, ios_base::in | ios::binary);
  bool model_found=false;
  bool model_saved=false;
  bool line_empty;
  bool commented_line_empty;
  vector<string> models_vector;

  while(getline(model_loaded, line))
    {
      line=remove_white_space(line);
      line_commented=line_remove_comment(line);
      line_empty=line.empty();
      commented_line_empty=line_commented.empty();

      if(line_empty or commented_line_empty)
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
