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
#include <fstream>
#include "read_constants.h"
#include "../global/global_constants.h"
#include "../global/read_bin_constants.h"
#include "../global/equations_map.h"
#include "../math/is_operator.h"
#include "../math/is_variable.h"
#include "../util/line_remove_comment.h"
#include "../util/remove_white_space.h"
#include "../util/vector_convert.h"
#include "../util/is_commented.h"
#include "../util/string_split.h"
#include "../util/valid_value_check.h"
#include "../util/s2d.h"

using std::fstream;
using std::ios_base;
using std::ios;
using std::to_string;

void equations_defined(const bool found)
{
  if(not found)
    {
      throw std::domain_error("Error, equations are not defined in "+BIN+" file.");
    }
}

const vector<string> equation_change_order(vector<string> equation)
{
  int i=0;
  int im1;
  int ip1;
  int size=equation.size()-1;
  bool variable_check;
  bool operator_check;
  string fchar;
  string fchar_im1;
  string fchar_ip1;

  while(i<=size)
    {
      fchar=equation[i];
      variable_check=is_variable(fchar);

      if(variable_check)
	{
	  im1=i-1;
	  ip1=i+1;

	  if(ip1>size)
	    {
	      break;
	    }

	  fchar_ip1=equation[ip1];
	  operator_check=is_operator(fchar_ip1);

	  if(operator_check)
	    {
	      equation.erase(equation.begin()+i, equation.begin()+ip1+1);
	      size=equation.size()-1;
	      equation.push_back(fchar_ip1);
	      equation.push_back(fchar);
	      i=0;
	      continue;
	    }
	}
      i++;
    }
  return equation;
}

void read_equation(const string line)
{
  const SplittedString splitted=string_split(line, EQUAL_SIGN);
  const string equation_name=splitted.splitted_string_part1;
  const string equation_value=splitted.splitted_string_part2;
  const vector<string> equation_read_result=equation_string_to_equation_vector2(equation_value);
  equations_map[equation_name]=equation_change_order(equation_read_result);
}

void read_bin(const string directory)
{
  int line_size;
  bool is_empty;
  bool is_line_commented;
  bool constants_found=false;
  bool constants_spec_found=false;
  bool equations_found=false;
  bool constants_saved=false;
  bool equations_saved=false;
  const string FILE_NAME=directory+BIN;
  const string CONST_BRACKET=CONSTANTS+CURLY_BRACKET_O;
  const string EQ_BRACKET=EQUATIONS+CURLY_BRACKET_O;
  string line;
  string line_commented;
  string constant_line;
  string initial_value_name;
  string initial_value;
  vector<SplittedString> specific_value_lines;
  SplittedString splitted;
  fstream bin_loaded(FILE_NAME, ios_base::in | ios::binary);
  unordered_map<string, string> constant_specific_map;
  double value_d;

  while(getline(bin_loaded, line))
    {
      line=remove_white_space(line);
      is_line_commented=is_commented(line);

      if(not is_line_commented)
	{
	  line_commented=line_remove_comment(line);
	  is_empty=line.empty();
	  line_size=line.size();

	  if(is_empty)
	    {
	      continue;
	    }
	  else if(not constants_saved)
	    {
	      if(line==CONSTANTS or line==CONST_BRACKET)
		{
		  constants_found=true;
		  continue;
		}
	      else if(line==CURLY_BRACKET_C and constants_found)
		{
		  constants_saved=true;
		  continue;
		}
	      else if(line==OPEN_PARENTHESIS)
		{
		  constants_spec_found=true;
		}
	      else if(line==CLOSE_PARENTHESIS)
		{
		  read_constants(constant_line, constant_specific_map);
		  constant_specific_map.clear();
		  constants_spec_found=false;
		}
	      else if(constants_found and line_size>1)
		{
		  if(not constants_spec_found)
		    {
		      constant_line=line;
		    }

		  if(constants_spec_found)
		    {
		      splitted=string_split(line, EQUAL_SIGN);

		      initial_value_name=splitted.splitted_string_part1;
		      initial_value=splitted.splitted_string_part2;

		      value_d=s2d(initial_value);
		      initial_value=to_string(value_d);

		      value_check(initial_value);
		      constant_specific_map[initial_value_name]=initial_value;
		    }
		  else
		    {
		      read_constants(line, constant_specific_map);
		    }
		}
	    }
	  else if(not equations_saved)
	    {
	      if(line==EQUATIONS or line==EQ_BRACKET)
		{
		  equations_found=true;
		  continue;
		}
	      else if(line==CURLY_BRACKET_C and equations_found)
		{
		  constants_saved=true;
		  continue;
		}
	      else if(equations_found and line_size>1)
		{
		  read_equation(line);
		}
	    }
	}
    }
  bin_loaded.close();
  equations_defined(equations_found);
}
