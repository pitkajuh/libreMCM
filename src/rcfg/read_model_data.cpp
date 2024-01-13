/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <stdexcept>
#include <sys/stat.h>
#include <fstream>
#include "../global/global_constants.h"
#include "../util/remove_white_space.h"
#include "../util/line_remove_comment.h"

using std::fstream;
using std::ios_base;
using std::ios;

// void model_find(const string line)
// {
//   const char* dir=line.c_str();
//   struct stat sb;

//   if(stat(dir, &sb)!=0)
//     {
//       throw std::domain_error("Path "+line+" was not found.");
//     }
// }

// const string read_model_line(const string line)
// {
//   int i=0;
//   const int size=line.size()-1;
//   string result="";
//   string fchar;

//   while(i<=size)
//     {
//       fchar=line[i];

//       if(fchar!=DELIMITER)
// 	{
// 	  result=result+fchar;
// 	}
//       i++;
//     }
//   return result;
// }

// const vector<string> read_model_data()
// {
//   bool model_found=false;
//   bool model_saved=false;
//   bool line_empty;
//   bool commented_line_empty;
//   const string model_location="model_path";
//   const string model_data_file="./models_cfg";
//   const string model_line=model_location+CURLY_BRACKET_O;
//   string line;
//   string line_commented;
//   fstream model_loaded(model_data_file, ios_base::in | ios::binary);
//   vector<string> models;

//   while(getline(model_loaded, line))
//     {
//       line=remove_white_space(line);
//       line_commented=line_remove_comment(line);
//       line_empty=line.empty();
//       commented_line_empty=line_commented.empty();

//       if(line_empty or commented_line_empty)
// 	{
// 	  continue;
// 	}
//       else if(not model_saved)
// 	{
// 	  if(line==CURLY_BRACKET_C and model_found)
// 	    {
// 	      model_saved=true;
// 	      continue;
// 	    }
// 	  else if(line==model_location or line==model_line)
// 	    {
// 	      model_found=true;
// 	      continue;
// 	    }
// 	  else if(model_found)
// 	    {
// 	      line=read_model_line(line);
// 	      model_find(line);
// 	      models.push_back(line);
// 	    }
// 	}
//     }
//   model_loaded.close();
//   return models;
// }
