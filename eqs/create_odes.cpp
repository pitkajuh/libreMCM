/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "../global/compartment_indice_data.h"
#include "../global/compartment_indice_data_upd.h"
#include "../global/odes.h"
#include "../global/odes_template_data.h"
#include "../global/total_equation_indices.h"
#include "../class/VecVecInt.h"
#include "../class/CompartmentTotalEquation.h"

vector<string> create_ode(const vector<string> ode_template, const vector<int> indices, const vector<string> iv_values)
{
  int i=0;
  int indice;
  const int size=indices.size()-1;
  string iv;
  vector<string> ode=ode_template;

  while(i<=size)
    {
      indice=indices[i];
      iv=iv_values[i];
      ode[indice]=iv;
      i++;
    }
  return ode;
}

void create_odes()
{
  int i=0;
  int j=0;
  const int size=compartment_indice_data.size()-1;
  const int eqs_size=odes.size()-1;
  string compartment_name;
  vector<int> indices;
  vector<string> ode_template;
  vector<string> ode;
  vector<string> ivs;
  CompartmentTotalEquation compartment_total_equation;
  IndicesData indices_data;

  while(i<=eqs_size)
    {
      ode_template=odes[i];
      indices_data=compartment_indice_data_upd[i];
      ivs=multiple_last_values[i];

      indices=indices_data.indices;
      ode=create_ode(ode_template, indices, ivs);

      indice_values.push_back(indices);
      equations.push_back(ode);
      i++;
    }
  math_op_indices=total_equation_indices;
  param_data=iv_indices_data;
}
