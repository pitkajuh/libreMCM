/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <unordered_map>
#include "../types/Csv.h"

using std::unordered_map;

void EquationAddSubtract(const unordered_map<string, string> equations_map, const Csv csv)
{
  const vector<Row> rows=csv.rows;
const vector<Column> columns=csv.columns;

  for(int i=0; i<rows.size(); i++)
    {

    }
}
