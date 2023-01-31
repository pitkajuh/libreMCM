/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <tuple>
#include <string>
#include <vector>

using namespace std;

vector<tuple<vector<string>, vector<int>, vector<string>>>
combine_equations_and_indices(vector<tuple<vector<string>, vector<int>, bool, vector<string>>> vector1, string compartment_name);
