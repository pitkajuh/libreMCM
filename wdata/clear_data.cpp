/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "../global/constants_map.h"
#include "../global/equations_map.h"
#include "../global/initial_value_map.h"
#include "../global/all_parameters.h"
#include "../global/all_values.h"
#include "../global/compartment_parameters.h"
#include "../global/compartment_diagonal_v2.h"
#include "../global/compartment_diagonal.h"
#include "../global/equations_with_compartment_name.h"
#include "../global/compartment_target_map.h"
#include "../global/column_map.h"
#include "../global/row_map.h"
#include "../global/compartment_map.h"
#include "../global/compartment_map_v2.h"
#include "../global/parameter_map.h"
#include "../global/compartments_and_equations_map.h"
#include "../global/initial_values_all.h"
#include "../global/constant_indice_data.h"
// #include "../global/compartment_total_equations_c.h"
#include "../global/compartment_total_equations.h"
#include "../global/compartment_indice_data.h"
#include "../global/total_equation_indices.h"
#include "../global/odes_template.h"
#include "../global/iv_indices_data.h"
#include "../global/iv_values_indice.h"
#include "../global/compartment_indice_data_upd.h"
#include "../global/odes.h"
// #include "../global/compartment_indice_sign.h"

#include <iostream>
using std::cout;

void clear_data()
{
  // cout<<"constants_map "<<constants_map.size()<<'\n';
  // cout<<"equations_map "<<equations_map.size()<<'\n';
  // cout<<"initial_value "<<initial_value_map.size()<<'\n';
  // cout<<"all_parameters "<<all_parameters.size()<<'\n';
  // cout<<"all_values "<<all_values.size()<<'\n';
  // cout<<"compartment_parameters "<<compartment_parameters.size()<<'\n';
  // cout<<"compartment_diagonal "<<compartment_diagonal_v2.size()<<'\n';
  // cout<<"compartment_diagonal "<<compartment_diagonal.size()<<'\n';
  // cout<<"compartment_target "<<compartment_target_map.size()<<'\n';
  // cout<<"column_map "<<column_map.size()<<'\n';
  // cout<<"row_map "<<row_map.size()<<'\n';
  // cout<<"compartment_map "<<compartment_map.size()<<'\n';
  // cout<<"compartment_map_v2 "<<compartment_map_v2.size()<<'\n';
  // cout<<"parameter_map "<<parameter_map.size()<<'\n'; // The size is already zero because parameter_map is cleared in file map/create_compartment_maps.cpp.
  // cout<<"compartments_and_equations "<<compartments_and_equations.size()<<'\n';
  // cout<<"initial_values_all "<<initial_values_all.size()<<'\n';
  // cout<<"equations_with_compartment_name "<<  equations_with_compartment_name.clear().size()<<'\n'; // Is already cleared in eqs/parse_compartment_equations.cpp.
  // cout<<"constant_indice_data "<<constant_indice_data.size()<<'\n';
  // cout<<"compartment_total_equations "<<compartment_total_equations.size()<<'\n';
  // cout<<"compartment_total_equations_c "<<compartment_total_equations_c.size()<<'\n';
  // cout<<"constant_indice_data "<<constant_indice_data.size()<<'\n';
  // cout<<"compartment_total_equations_c "<<compartment_total_equations_c.size()<<'\n';
  // cout<<"compartment_total_equations "<<compartment_total_equations.size()<<'\n';
  // cout<<"compartment_indice_data "<<compartment_indice_data.size()<<'\n';
  // cout<<"total_equation_indices "<<total_equation_indices.size()<<'\n';

  // cout<<"des.clear() "<<des.size()<<'\n';
  // cout<<"iv_indices_data.size() "<<iv_indices_data.size()<<'\n';
  // cout<<"multiple_last_values.size() "<<multiple_last_values.size()<<'\n';
  // cout<<"compartment_indice_data.size() "<<compartment_indice_data.size()<<'\n';
  // cout<<"compartment_indice_data_upd.size() "<<compartment_indice_data.size()<<'\n';

  constants_map.clear();
  equations_map.clear();
  initial_value_map.clear();
  all_parameters.clear();
  all_values.clear();
  compartment_parameters.clear();
  compartment_diagonal_v2.clear();
  compartment_diagonal.clear();
  compartment_target_map.clear();
  column_map.clear();
  row_map.clear();
  compartment_map.clear();
  compartment_map_v2.clear();
  parameter_map.clear();
  compartments_and_equations.clear();
  initial_values_all.clear();
  // equations_with_compartment_name.clear();
  constant_indice_data.clear();
  compartment_total_equations.clear();
  // compartment_total_equations_c.clear();

  constant_indice_data.clear();
  // compartment_total_equations_c.clear();
  compartment_total_equations.clear();
  compartment_indice_data.clear();
  total_equation_indices.clear();

  odes.clear();
  iv_indices_data.clear();
  multiple_last_values.clear();
  compartment_indice_data.clear();
  compartment_indice_data_upd.clear();

  equations.clear();
  indice_values.clear();
  total_equation_indices.clear();
  iv_indices_data.clear();
  // is_compartment_indice_neg.clear();
}
