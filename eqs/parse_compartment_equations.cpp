/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "get_indices.h"
#include "../global/compartment_total_equations.h"
#include "../global/global_constants.h"
#include "../global/equations_with_compartment_name.h"
#include "../util/combine_vectors.h"
#include "../math/is_operator.h"

vector<string> reverse_sign(const vector<string> fa)
{
  bool is_math_op;
  bool subtract_begin=false;
  int i=0;
  int ip1;
  int im1;
  const int zero_value=0;
  int size=fa.size()-1;
  string fchar;
  string fchar_sign;
  string fa_ip1;
  string fa_ip1_sign;
  string fa_im1;
  vector<string> vec_new;

  while(i<=size)
    {
      fchar=fa[i];
      fchar_sign=fchar[0];

      if(fchar==OPEN_PARENTHESIS or fchar==CLOSE_PARENTHESIS)
	{
	  vec_new.push_back(fchar);
	}
      else if(fchar_sign==SUBTRACT)
	{
	  fchar.erase(fchar.begin()+zero_value);
	  vec_new.push_back(ADD);
	  vec_new.push_back(fchar);
	  i++;
	  continue;
	}
      else if(fchar==ADD)
	{
	  ip1=i+1;
	  fa_ip1=fa[ip1];
	  fa_ip1_sign=fa_ip1[0];
	  vec_new.push_back(fchar);

	  if(fa_ip1_sign==SUBTRACT)
	    {
	      fa_ip1.erase(fa_ip1.begin()+zero_value);
	      vec_new.push_back(fa_ip1);
	    }
	  else
	    {
	      fa_ip1=SUBTRACT+fa_ip1;
	      vec_new.push_back(fa_ip1);
	    }
	  i=i+2;
	  continue;
	}
      else if(i<size and i>0)
	{
	  is_math_op=is_operator(fchar);
	  im1=i-1;
	  fa_im1=fa[im1];

	  if(!is_math_op and fa_im1!=MULTIPLY and fa_im1!=DIVIDE)
	    {
	      ip1=i+1;
	      fa_ip1=fa[ip1];

	      if(fa_ip1==ADD and not subtract_begin)
		{
		  fchar=SUBTRACT+fchar;
		}
	    }
	  vec_new.push_back(fchar);
	}
      else
	{
	  if(i==0)
	    {
	      fchar=SUBTRACT+fchar;
	      subtract_begin=true;
	    }

	  vec_new.push_back(fchar);
	}
      i++;
    }
  return vec_new;
}

vector<string> parse(Equations equations)
{
  int i=0;
  const int size=equations.size()-1;
  vector<string> equation;
  vector<string> equation_total;

  if(size==0)
    {
      equation_total=equations[0];
    }
  else
    {
      while(i<=size)
	{
	  equation=equations[i];

	  if(i<size)
	    {
	      equation.push_back(ADD);
	    }
	  equation_total=combine_vectors(equation, equation_total);
	  i++;
	}
    }
  return equation_total;
}

vector<string> combine(Equations equations_add_all, Equations equations_subtract_all)
{
  // All transfer equations acting on a single compartment will be combined into single larger equation. Thus there is only one ODE per compartment.
  int i=0;
  const int add_size=equations_add_all.size();
  const int subtract_size=equations_subtract_all.size();
  vector<string> equation_total;
  vector<string> equation_add;
  vector<string> equation_subtract;

  if(add_size>0 and subtract_size==0)
    {
      equation_total=parse(equations_add_all);
    }
  else if(add_size==0 and subtract_size>0)
    {
      equation_total=parse(equations_subtract_all);
      equation_total=reverse_sign(equation_total);
    }
  else
    {
      equation_add=parse(equations_add_all);
      equation_add.push_back(ADD);
      equation_subtract=parse(equations_subtract_all);
      equation_subtract=reverse_sign(equation_subtract);
      equation_total=combine_vectors(equation_subtract, equation_add);
    }
  return equation_total;
}

void parse_compartment_equations()
{
  int i=0;
  const int size=equations_with_compartment_name.size()-1;
  string compartment_name;
  vector<string> equation_total;
  Equations equations_add;
  Equations equations_subtract;
  CompartmentEquationsAddSubtract equation_data;
  CompartmentTotalEquation data;

  while(i<=size)
    {
      equation_data=equations_with_compartment_name[i];
      compartment_name=equation_data.compartment;

      // Equations acting on void and origin compartment types are not interesting from the point of view of numerical calculation.
      if(compartment_name!=VOID and compartment_name!=ORIGIN)
	{
	  equations_add=equation_data.equations_add;
	  equations_subtract=equation_data.equations_subtract;
	  equation_total=combine(equations_add, equations_subtract);
	  get_indices(equation_total);
	  data.compartment_name=compartment_name;
	  data.total_equation=equation_total;
	  compartment_total_equations.push_back(data);
	}
      i++;
    }
  equations_with_compartment_name.clear();
}
