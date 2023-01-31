/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "read_config_sub.h"
#include "../global/global.h"
#include "../math/is_operator.h"
#include "../math/calculate_order_of_operations.h"
#include "../util/replace_in_vector.h"
#include "../util/combine_vectors.h"
#include "../util/vector_convert.h"
#include "../util/vector_split.h"
#include "../rcfg/read_model_data.h"

using namespace std;

vector<string> variables;
vector<tuple<string, string>> func_params;
vector<tuple<string, vector<string>>> equations;

void equation_set_order_subsub(vector<string> fa, vector<tuple<int, int>> indices, int move_to_index)
{
  int i=0;
  vector<string> fa_splitted;
  tuple<int, int> indices_i;
  int from;
  int to;
  int sign_i;
  string sign;

  if(indices.size()>0)
    {
      while(i<=indices.size()-1)
	{
	  indices_i=indices[i];
	  from=get<0>(indices_i);
	  to=get<1>(indices_i);
	  fa_splitted=vector_split(fa, from, to);
	  sign_i=from-1;

	  if(sign_i>0)
	    {
	      sign=fa[sign_i];
	    }
	  else
	    {
	      sign=add;
	    }

	  i++;
	}
    }
}

vector<string> splitted_vector(vector<string> fa, int from, int to, int move_to)
{
  vector<string> vector_part1;
  vector<string> vector_part2;
  vector<string> combined;
  const int zero_value=0;
  int from_up;
  vector<string> fa_splitted_move;
  string sign_i;
  string sign_j;
  int difference=to-from;
  string variable;
  string replace;

  if(to<fa.size()-1)
    {
      sign_i=fa[from];

      if(difference==1 and sign_i==add)
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
	  vector_part2=vector_split(fa, to, fa.size()-1);
	  fa_splitted_move=vector_split(fa, from, to);
	}
    }
  else
    {
      sign_i=fa[from];

      if(difference==1 and sign_i==add)
	{
	  from=from+1;
	  variable=fa[from];
	  replace=fa[move_to];
	  fa[move_to]=variable;
	  fa[from]=replace;
	  combined=fa;
	}
      else if(sign_i==subtract)
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
	  combined=combine_vectors2(vector_part2, fa_splitted_move);
	}
    }

  return combined;
}

vector<string> variable_has_coefficient_neg_dir(vector<string> fa, int start, int move_to)
{
  int i_pos=start;
  int i_neg=start;
  string fchar;
  bool stop_pos_dir=false;
  bool stop_neg_dir=false;
  int i_stop;
  int rt_start;
  int rt_stop;
  tuple<int, int> indices;
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

      if(fchar==add or fchar==subtract or fchar==open_parenthesis or fchar==close_parenthesis)
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
  string fchar;
  bool is_fchar_variable;
  string variable;
  string replace;
  int move_to=0;
  int fa_size=fa.size();

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
  int i=0;
  string fchar;
  int open;
  int close;
  vector<string> fa_sub;
  vector<string> fa_splitted;
  string fa_sub_str;
  string fa_str;

  while(i<=fa.size()-1)
    {
      fchar=fa[i];

      if(fchar==open_parenthesis)
	{
	  open=i+1;
	}
      else if(fchar==close_parenthesis)
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

  string result;
  vector<string> result_vec;
  int i=0;
  int fa_size=fa.size();
  int o_index;
  int c_index;
  string fchar;
  vector<string> rt_value;
  vector<int> parenthesis_open_indices;
  vector<int> parenthesis_close_indices;
  vector<string> ooo_result_vec;
  string ooo_result;
  vector<string> vector_convert;
  vector<string> vector_combined;

  while(i<=fa_size-1)
    {
      fchar=fa[i];

      if(fchar==open_parenthesis)
	{
	  parenthesis_open_indices.push_back(i);
	}
      else if(fchar==close_parenthesis)
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

vector<string> equation_read(string func_name, string func_value)
{
  int i=0;
  int last_operator_index;
  vector<string> fa;
  const string empty_str="";
  string abb=empty_str;
  string fchar;
  vector<string> read_bin_result;
  bool is_str_operator;
  string sub_string;
  int i_substr_from;
  int i_substr_to;

  while(i<=func_value.size()-1)
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
	      abb=empty_str;
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

  if(last_operator_index!=func_value.size()-1)
    {
      i_substr_from=last_operator_index+1;
      i_substr_to=func_value.size()-1-last_operator_index;
      sub_string=func_value.substr(i_substr_from, i_substr_to);
      fa.push_back(sub_string);
    }

  read_bin_result=calculate_equation_constants(fa);
  return read_bin_result;
}

tuple<string, vector<string>> read_equations(string line)
{
  int i=0;
  string fchar;
  string ab;
  string empty_str="";
  string equation_name;
  string equation_value;
  bool eq_found=false;
  vector<string> equation_read_result;
  tuple<string, vector<string>> rt;
  const string empty1=" ";
  const string empty2="\0";

  while(i<=line.size()-1)
  {
    fchar=line[i];

      if(fchar==delimiter)
	{
	  equation_value=ab;
	}
      else if(fchar==empty2 or fchar==empty1 or fchar.empty())
	{
	  i++;
	  continue;
	}
      else if(fchar==equal_sign)
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
  rt=make_tuple(equation_name, equation_read_result);
  return rt;
}

string get_variable(string line)
{
  int i=0;
  string fchar;
  string variable;
  string ab;
  const string empty1=" ";
  const string empty2="\0";

  while(i<=line.size()-1)
    {
      fchar=line[i];

      if(fchar==delimiter)
	{
	  variable=ab;
	  break;
	}
      else if(fchar==empty2 or fchar==empty1 or fchar.empty())
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

void read_bin(string directory)
{
  const string file_name=directory+"bin";
  const string constants_str="constants";
  const string equations_str="equations";
  const string variables_str="variables";
  fstream bin_loaded(file_name, ios_base::in | ios::binary);
  string line;
  string get_variable_result;
  string line_commented;
  bool constants_found=false;
  bool equations_found=false;
  bool variables_found=false;
  bool constants_saved=false;
  bool equations_saved=false;
  bool variables_saved=false;
  tuple<string, string> read_constants_result;
  tuple<string, vector<string>> read_equations_result;
  vector<tuple<string, vector<string>>> rt;

  while(getline(bin_loaded, line))
    {
      line_commented=line_commented_or_not(line);

      if(line.empty() or line_commented.empty())
	{
	  continue;
	}
      else if(!variables_saved)
	{
	  if(line==curly_bracket_c and variables_found)
	    {
	      variables_saved=true;
	      continue;
	    }
	  else if(line==variables_str or line==variables_str+curly_bracket_o)
	    {
	      variables_found=true;
	      continue;
	    }
	  else if(variables_found)
	    {
	      get_variable_result=get_variable(line);
	      variables.push_back(get_variable_result);
	    }
	}
      else if(!constants_saved)
	{
	  if(line==curly_bracket_c and constants_found)
	    {
	      constants_saved=true;
	      continue;
	    }
	  else if(line==constants_str or line==constants_str+curly_bracket_o)
	    {
	      constants_found=true;
	      continue;
	    }
	  else if(constants_found)
	    {
	      read_constants_result=read_constants(line);
	      func_params.push_back(read_constants_result);
	    }
	}
      else if(!equations_saved)
	{
	  if(line==curly_bracket_c and equations_found)
	    {
	      constants_saved=true;
	      continue;
	    }
	  else if(line==equations_str or line==equations_str+curly_bracket_o)
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

string get_constant_value(string constant)
{
  int i=0;
  bool value_found=false;
  bool constant_size_2=false;
  string value_found_return;
  double value_found_return_double;
  string compare;
  tuple<string, string> func_params_i;

  if(constant.size()==2)
    {
      constant=constant[1];
      constant_size_2=true;
    }

  while(i<=func_params.size()-1)
    {
      func_params_i=func_params[i];
      compare=get<0>(func_params_i);

      if(constant==compare)
	{
	  value_found=true;
	  value_found_return=get<1>(func_params_i);
	  value_found_return_double=stod(value_found_return);
	  value_found_return=to_string(value_found_return_double);

	  if(constant_size_2)
	    {
	      value_found_return=subtract+value_found_return;
	    }

	  break;
	}
      i++;
    }



  if(value_found)
    {
      return value_found_return;
    }
  else
    {
      cout<<"Error, constant value for "<<constant<<" not found"<<endl;
      return NULL;
    }

}

void get_equations(string directory)
{
  read_bin(directory);
  func_params.clear();
}
