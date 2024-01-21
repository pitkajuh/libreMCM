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
#include "../global/compartment_total_equations.h"
#include "../global/compartment_indice_data.h"
#include "../global/total_equation_indices.h"
#include "../global/odes_template.h"
#include "../global/iv_indices_data.h"
#include "../global/iv_values_indice.h"
#include "../global/compartment_indice_data_upd.h"
#include "../global/odes.h"
#include "../global/ode_indice_operator_prev.h"
#include "../global/ode_indice_operator.h"

void clear_data()
{
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
  constant_indice_data.clear();
  compartment_total_equations.clear();

  constant_indice_data.clear();
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
  ode_indice_operator_prev.clear();
  ode_indice_operator.clear();
}
