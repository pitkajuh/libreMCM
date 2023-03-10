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

using std::string;
using std::vector;

vector<string> vector_split(vector<string> fa, int start, int stop)
{
  int i=start;
  string emp="";
  string fchar;
  vector<string> rt;

  while(i<=stop)
    {
      fchar=fa[i];
      rt.push_back(fchar);
      emp=emp+fchar;
      i++;
    }
  return rt;
}
