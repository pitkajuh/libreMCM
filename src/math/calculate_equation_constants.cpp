/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "../global/global_constants.h"
#include "../global/equations_map.h"
#include "../class/EquationName.h"
#include "../math/is_variable.h"
#include "../math/calculate_order_of_operations.h"
#include "../util/replace_in_vector.h"
#include "../util/vector_convert.h"
#include "../util/combine_vectors.h"
#include "../util/vector_split.h"

vector<string> splitted_vector(vector<string> fa, int from, const int to, const int move_to)
{
  const int zero_value=0;
  const int size=fa.size();
  int from_up;
  int difference=to-from;
  string sign_i;
  string sign_j;
  string variable;
  string replace;
  vector<string> vector_part1;
  vector<string> vector_part2;
  vector<string> combined;
  vector<string> fa_splitted_move;

  if(to<size-1)
    {
      sign_i=fa[from];

      if(difference==1 and sign_i==ADD)
	{
	  from+=1;
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
	  from+=1;
	  variable=fa[from];
	  replace=fa[move_to];
	  fa[move_to]=variable;
	  fa[from]=replace;
	  combined=fa;
	}
      else if(sign_i==SUBTRACT){combined=fa;}
      else
	{
	  from+=1;
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
  vector<string> combined_vector;

  while(!stop_neg_dir)
    {
      if(i_neg<=0){break;}
      fchar=fa[i_neg];

      if(fchar==ADD or fchar==SUBTRACT or fchar==OPEN or fchar==CLOSE)
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
  if(!stop_neg_dir){combined_vector=fa;}
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

      if(fchar==OPEN){open=i+1;}
      else if(fchar==CLOSE)
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
  int fa_size=fa.size()-1;
  int o_index;
  int c_index;
  int close_size;
  int open_size;
  int size2;
  bool has_open_parenthesis=false;
  bool has_close_parenthesis=false;
  string result;
  string ooo_result;
  string fchar;
  vector<string> rt_value;
  vector<string> ooo_result_vec;
  vector<int> parenthesis_open_indices;
  vector<int> parenthesis_close_indices;

  while(i<=fa_size)
    {
      fchar=fa[i];

      if(fchar==OPEN)
	{
	  has_open_parenthesis=true;
	  parenthesis_open_indices.push_back(i);
	}
      else if(fchar==CLOSE)
	{
	  has_close_parenthesis=true;
	  parenthesis_close_indices.push_back(i);
	  close_size=parenthesis_close_indices.size();
	  open_size=parenthesis_open_indices.size();

	  if(close_size==1 and open_size>=1)
	    {
	      o_index=parenthesis_open_indices.back();
	      c_index=parenthesis_close_indices.back();
	      rt_value=vector_split(fa, o_index, c_index);
	      ooo_result_vec=calculate_order_of_operations(rt_value);
	      size2=ooo_result_vec.size();

	      if(size2==1)
		{
		  ooo_result=ooo_result_vec[0];
		  fa=replace_in_vector(fa, ooo_result, o_index, c_index);
		}
	      else
		{
		  parenthesis_open_indices.clear();
		  parenthesis_close_indices.clear();
		  fa_size=fa.size()-1;
		  break;
		}
	      parenthesis_open_indices.clear();
	      parenthesis_close_indices.clear();
	      fa_size=fa.size()-1;
	      i=0;
	      continue;
	    }
	}
      i++;
    }

  if(has_open_parenthesis and has_close_parenthesis){fa=equation_set_order(fa);}
  fa=calculate_order_of_operations(fa);
  return fa;
}
