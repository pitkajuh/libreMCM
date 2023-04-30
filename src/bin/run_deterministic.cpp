/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "../eqs/create_odes_templates.h"
#include "../eqs/create_odes.h"
#include "../num/numerical_calculation.h"
#include "../wdata/clear_data.h"
#include "../wdata/write_to_file.h"

void run_deterministic(const string model)
{
  const int run_no=0;
  create_odes_templates();
  create_odes();
  numerical_calculation_start();
  write_to_file(model, run_no);
  clear_data();
}
