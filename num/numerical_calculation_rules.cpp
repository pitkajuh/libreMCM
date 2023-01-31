/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <vector>
#include "../math/calculate_order_of_operations.h"
#include "../global/global.h"
#include "../util/vector_convert.h"
#include "../util/replace_in_vector.h"
#include "../util/combine_vectors.h"
#include "../util/vector_split.h"

using namespace std;

vector<int> numerical_calculation_rules_rt;

string calculate_order_of_operations3(vector<string> fa, int add_index)
{
  int i=0;
  int j=0;
  string fchar;
  string rt;
  string res;
  string calc_result;
  int fa_size=fa.size();
  int fa_size_prev;
  vector<int> indices;
  const vector<string> operators={power, multiply, divide, add, subtract};
  string operators_i;
  int result_index;

  while(j<=operators.size()-1)
    {
      if(i>fa_size-1)
	{
	  i=0;
	  continue;
	}

      fchar=fa[i];
      operators_i=operators[j];

      if(i==fa_size-1)
	{
	  j++;
	  i=0;
	  fa_size=fa.size();
	  continue;
	}


      if(fchar==operators_i)
	{
	  result_index=add_index+i;
	  fa_size_prev=fa.size();
	  fa=do_calculation(fa, i);
	  fa_size=fa.size();
	  i=i-fa_size_prev+fa_size;
	  numerical_calculation_rules_rt.push_back(result_index);

	  if(fa_size-1==0)
	    {
	      break;
	    }
	}

      i++;
    }

  rt=vector_to_string(fa);
  return rt;
}

vector<string> get_parenthesis_calculation_indices(vector<string> fa)
{
  int i=0;
  int fa_size=fa.size();
  string fchar;
  int o_index;
  int c_index;
  vector<string> rt_value;
  vector<int> parenthesis_open_indices;
  vector<int> parenthesis_close_indices;
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
	      ooo_result=calculate_order_of_operations3(rt_value, o_index);
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

  return fa;
}

vector<int> numerical_calculation_rules(vector<string> fa)
{
  int i=0;
  int j=0;
  string fchar;
  string math_operator;
  vector<string> operators={power, divide, multiply, add, subtract};
  string calculation_result;
  int im1;
  int ip1;
  string fa_im1;
  string fa_ip1;
  vector<int> return_indices;
  int fa_size=fa.size();

  fa=get_parenthesis_calculation_indices(fa);
  fa_size=fa.size();

  while(i<=operators.size()-1)
    {
      math_operator=operators[i];

      while(j<=fa_size-1)
	{
	  if(fa_size-1==0)
	    {
	      break;
	    }

	  fchar=fa[j];

	  if(math_operator==fchar)
	    {
	      im1=j-1;
	      ip1=j+1;
	      fa_im1=fa[im1];
	      fa_ip1=fa[ip1];
	      calculation_result=get_math_operator(fa_im1, fa_ip1, math_operator);
	      fa=replace_in_vector(fa, calculation_result, im1, ip1);
	      fa_size=fa.size();
	      numerical_calculation_rules_rt.push_back(j);

	      if(fa_size-1==0)
		{
		  break;
		}

	      j=0;
	      continue;
	    }
	  j++;
	}

      j=0;
      i++;
    }

  return_indices=numerical_calculation_rules_rt;
  numerical_calculation_rules_rt.clear();
  return return_indices;
}
