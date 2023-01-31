/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <string>
#include <vector>

using namespace std;

extern vector<tuple<string, vector<vector<string>>, vector<vector<string>>>> equations_with_compartment_name;
extern vector<tuple<string, vector<tuple<string, string, int>>>> all_values;
extern vector<tuple<string, bool, vector<vector<string>>>> rt_local_global;

vector<tuple<string, vector<tuple<string, string, int>>>> parse_compartment_equations_subsubroutine();
void parse_compartment_equations_subroutine(vector<vector<string>> compartment_vector);
void parse_compartment_equations();
