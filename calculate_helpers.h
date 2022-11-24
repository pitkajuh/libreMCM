/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

using namespace std;

tuple<string, bool, vector<vector<string>>> abc(string equation, bool equation_add, string compartment_name, int compartment_start_index, int index1);
vector<tuple<string, string, int>> get_compartment_elements_by_compartment_name(string compartment_name);
int get_compartment_index (string compartment_name);
