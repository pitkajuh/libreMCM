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

extern vector<tuple<
	 string, // compartment name
	 vector<
	   tuple<
	     string, // parameter name
	     vector<
	       string // parameter values
	       >>>>> params_graph;
void add_all_values ();
