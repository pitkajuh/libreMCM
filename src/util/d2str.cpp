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
#include <sstream>

using std::string;
using std::ostringstream;

const string d2str(const double value)
{
  ostringstream res;
  res<<value;
  const string result=res.str();
  return result;
}
