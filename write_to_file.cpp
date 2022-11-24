/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "global.h"
#include "numerical_calculation.h"


using namespace std;

void write_to_file()
{
  int i=0, j=0;
  double t=0;
  string str;
  ofstream myfile ("r.txt");

  while(j<=get<1>(get<1>(params_graph_up[i])[0]).size()-1)
    {
      str=str+to_string(t)+delimiter;
      str=str+get<1>(get<1>(params_graph_up[i])[0])[j];

      i++;

      str=str+delimiter;
      str=str+get<1>(get<1>(params_graph_up[i])[0])[j];
      str=str+"\n";

      j++;
      i--;

      t=t+h;
    }

   myfile<<str;
   myfile.close ();
}
