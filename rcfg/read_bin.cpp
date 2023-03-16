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
#include "read_constants.h"
#include "read_model_data.h"
#include "../class/EquationNamesValues.h"
#include "../global/global.h"
#include "../math/is_operator.h"
#include "../math/is_variable.h"
#include "../math/calculate_order_of_operations.h"
#include "../util/replace_in_vector.h"
#include "../util/combine_vectors.h"
#include "../util/vector_convert.h"
#include "../util/vector_split.h"
#include "../util/line_remove_comment.h"

using std::map;
using std::fstream;
using std::ios_base;
using std::ios;

Constants constants;
EquationNamesValues equations;
map<string, vector<string>> equations_map;

vector<string> splitted_vector(vector<string> fa, int from, const int to, const int move_to)
{
  const int zero_value=0;
  const int size=fa.size();
  int from_up;
  int difference=to-from;
  vector<string> vector_part1;
  vector<string> vector_part2;
  vector<string> combined;
  vector<string> fa_splitted_move;
  string sign_i;
  string sign_j;
  string variable;
  string replace;

  if(to<size-1)
    {
      sign_i=fa[from];

      if(difference==1 and sign_i==ADD)
	{
	  from=from+1;
	  variable=fa[from];
	  replace=fa[move_to];
	  fa[move_to]=variable;
	  fa[from]=replace;
	  combined=fa;
	}
      else
	{
	  vector_part2=vector_split(fa, to, size-1);
	  fa_splitted_move=vector_split(fa, from, to);
	}
    }
  else
    {
      sign_i=fa[from];

      if(difference==1 and sign_i==ADD)
	{
	  from=from+1;
	  variable=fa[from];
	  replace=fa[move_to];
	  fa[move_to]=variable;
	  fa[from]=replace;
	  combined=fa;
	}
      else if(sign_i==SUBTRACT)
	{
	  combined=fa;
	}
      else
	{
	  from=from+1;
	  fa_splitted_move=vector_split(fa, from, to);
	  fa_splitted_move.push_back(sign_i);
	  from_up=from-2;
	  vector_part2=vector_split(fa, zero_value, from_up);
	  sign_j=vector_part2[zero_value];
	  combined=combine_vectors(vector_part2, fa_splitted_move);
	}
    }
  return combined;
}

vector<string> variable_has_coefficient_neg_dir(const vector<string> fa, const int start, const int move_to)
{
  int i_pos=start;
  int i_neg=start;
  int i_stop;
  int rt_start;
  int rt_stop;
  string fchar;
  bool stop_pos_dir=false;
  bool stop_neg_dir=false;
  vector<string> fa_splitted_move;
  vector<string> fa_splitted_remove;
  vector<string> combined_vector;

  while(!stop_neg_dir)
    {
      if(i_neg<=0)
	{
	  break;
	}
      fchar=fa[i_neg];

      if(fchar==ADD or fchar==SUBTRACT or fchar==OPEN_PARENTHESIS or fchar==CLOSE_PARENTHESIS)
	{
	  i_stop=i_neg;
	  rt_stop=start;
	  rt_start=i_stop;
	  stop_neg_dir=true;
	  combined_vector=splitted_vector(fa, rt_start, rt_stop, move_to);
	  break;
	}
      i_neg--;
    }
  if(!stop_neg_dir)
    {
      combined_vector=fa;
    }
  return combined_vector;
}

vector<string> equation_set_order_sub(vector<string> fa)
{
  int i=0;
  int move_to=0;
  int fa_size=fa.size();
  string fchar;
  string variable;
  bool is_fchar_variable;

  while(i<=fa_size-1)
    {
      fchar=fa[i];
      is_fchar_variable=is_variable(fchar);

      if(is_fchar_variable)
	{
	  variable=fchar;
	  fa=variable_has_coefficient_neg_dir(fa, i, move_to);
	  fa_size=fa.size();
	  move_to++;
	}
      i++;
    }
  return fa;
}

vector<string> equation_set_order(vector<string> fa)
{
  const int size=fa.size();
  int i=0;
  int open;
  int close;
  string fchar;
  string fa_sub_str;
  string fa_str;
  vector<string> fa_sub;
  vector<string> fa_splitted;

  while(i<=size-1)
    {
      fchar=fa[i];

      if(fchar==OPEN_PARENTHESIS)
	{
	  open=i+1;
	}
      else if(fchar==CLOSE_PARENTHESIS)
	{
	  close=i-1;
	  fa_splitted=vector_split(fa, open, close);
	  fa_sub=equation_set_order_sub(fa_splitted);
	  fa_sub_str=vector_to_string (fa_sub);
	  fa=replace_in_vector2(fa, fa_sub_str, open, close);
	  fa_str=vector_to_string(fa);
	  fa=equation_string_to_equation_vector(fa_str);
	}
      i++;
    }
  return fa;
}

vector<string> calculate_equation_constants(vector<string> fa)
{
  /*
    Calculates an equation according to order of operations:

    1. Parentheses
    2. Exponents
    3. Multiplication and division
    4. Addition and subtraction
  */

  int i=0;
  int fa_size=fa.size();
  int o_index;
  int c_index;
  string result;
  string ooo_result;
  string fchar;
  vector<string> result_vec;
  vector<string> rt_value;
  vector<string> ooo_result_vec;
  vector<int> parenthesis_open_indices;
  vector<int> parenthesis_close_indices;

  while(i<=fa_size-1)
    {
      fchar=fa[i];

      if(fchar==OPEN_PARENTHESIS)
	{
	  parenthesis_open_indices.push_back(i);
	}
      else if(fchar==CLOSE_PARENTHESIS)
	{
	  parenthesis_close_indices.push_back(i);

	  if(parenthesis_close_indices.size()==1 and parenthesis_open_indices.size()>=1)
	    {
	      o_index=parenthesis_open_indices.back();
	      c_index=parenthesis_close_indices.back();
	      rt_value=vector_split(fa, o_index, c_index);
	      ooo_result_vec=calculate_order_of_operations2(rt_value);
	      ooo_result=vector_to_string(ooo_result_vec);
	      fa=replace_in_vector(fa, ooo_result, o_index, c_index);

	      parenthesis_open_indices.clear();
	      parenthesis_close_indices.clear();
	      fa_size=fa.size();
	      i=0;
	      continue;
	    }
	}
      i++;
    }
  result=vector_to_string(fa);
  fa=equation_string_to_equation_vector(result);
  fa=equation_set_order(fa);
  result_vec=calculate_order_of_operations2(fa);
  return result_vec;
}

vector<string> equation_read(const string func_name, const string func_value)
{
  int i=0;
  int size=func_value.size();
  int last_operator_index;
  int i_substr_from;
  int i_substr_to;
  vector<string> fa;
  vector<string> read_bin_result;
  string abb="";
  string fchar;
  string sub_string;
  bool is_str_operator;

  while(i<=size-1)
    {
      fchar=func_value[i];
      is_str_operator=is_operator(fchar);

      if(is_str_operator and i==0)
	{
	  fa.push_back(fchar);
	}
      else if(is_str_operator)
	{
	  if(abb.length()>0)
	    {
	      fa.push_back(abb);
	      abb="";
	    }
	  fa.push_back(fchar);
	  last_operator_index=i;
	}
      else
	{
	  abb=abb+fchar;
	}
      i++;
    }

  size=func_value.size();

  if(last_operator_index!=size-1)
    {
      i_substr_from=last_operator_index+1;
      i_substr_to=size-1-last_operator_index;
      sub_string=func_value.substr(i_substr_from, i_substr_to);
      fa.push_back(sub_string);
    }
  read_bin_result=calculate_equation_constants(fa);
  return read_bin_result;
}

EquationName read_equations(const string line)
{
  int i=0;
  const int size=line.size();
  string fchar;
  string ab;
  string empty_str="";
  string equation_name;
  string equation_value;
  const string empty1=" ";
  const string empty2="\0";
  bool eq_found=false;
  bool is_empty;
  vector<string> equation_read_result;
  EquationName rt;

  while(i<=size-1)
  {
    fchar=line[i];
    is_empty=fchar.empty();

    if(fchar==DELIMITER)
      {
	equation_value=ab;
      }
    else if(fchar==empty2 or fchar==empty1 or is_empty)
      {
	i++;
	continue;
      }
    else if(fchar==EQUAL_SIGN)
      {
	equation_name=ab;
	ab=empty_str;
	eq_found=true;
      }
    else
      {
	ab=ab+fchar;
      }
    i++;
  }

  equation_read_result=equation_read(equation_name, equation_value);
  equations_map[equation_name]=equation_read_result;
  rt.equation_name=equation_name;
  rt.equation=equation_read_result;
  return rt;
}

string get_variable(const string line)
{
  int i=0;
  const int size=line.size();
  string fchar;
  string variable;
  string ab;
  const string empty1=" ";
  const string empty2="\0";
  bool is_empty;

  while(i<=size-1)
    {
      fchar=line[i];
      is_empty=fchar.empty();

      if(fchar==DELIMITER)
	{
	  variable=ab;
	  break;
	}
      else if(fchar==empty2 or fchar==empty1 or is_empty)
	{
	  i++;
	  continue;
	}
      else
	{
	  ab=ab+fchar;
	}
      i++;
    }
  return variable;
}

void read_bin(const string directory)
{
  const string file_name=directory+"bin";
  const string constants_str="constants";
  const string equations_str="equations";
  const string const_bracket=constants_str+CURLY_BRACKET_O;
  const string eq_bracket=equations_str+CURLY_BRACKET_O;
  fstream bin_loaded(file_name, ios_base::in | ios::binary);
  string line;
  string line_commented;
  bool constants_found=false;
  bool equations_found=false;
  bool constants_saved=false;
  bool equations_saved=false;
  bool is_empty;
  bool is_empty2;
  ConstantNameAndValue read_constants_result;
  EquationName read_equations_result;
  EquationNamesValues rt;

  while(getline(bin_loaded, line))
    {
      line_commented=line_remove_comment(line);
      is_empty=line.empty();
      is_empty2=line_commented.empty();

      if(is_empty or is_empty2)
	{
	  continue;
	}
      else if(!constants_saved)
	{
	  if(line==CURLY_BRACKET_C and constants_found)
	    {
	      constants_saved=true;
	      continue;
	    }
	  else if(line==constants_str or line==const_bracket)
	    {
	      constants_found=true;
	      continue;
	    }
	  else if(constants_found)
	    {
	      read_constants_result=read_constants(line);
	      constants.push_back(read_constants_result);
	    }
	}
      else if(!equations_saved)
	{
	  if(line==CURLY_BRACKET_C and equations_found)
	    {
	      constants_saved=true;
	      continue;
	    }
	  else if(line==equations_str or line==eq_bracket)
	    {
	      equations_found=true;
	      continue;
	    }
	  else if(equations_found)
	    {
	      read_equations_result=read_equations(line);
	      rt.push_back(read_equations_result);
	    }
	}
    }
  equations=rt;
}
