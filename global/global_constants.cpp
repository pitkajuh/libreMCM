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

extern const string MULTIPLY="*";
extern const string DIVIDE="/";
extern const string ADD="+";
extern const string SUBTRACT="-";
extern const string POWER="^";
extern const string OPEN_PARENTHESIS="(";
extern const string CLOSE_PARENTHESIS=")";
extern const string COMMENT="//";
extern const string CURLY_BRACKET_O="{";
extern const string CURLY_BRACKET_C="}";
extern const string PARM_DELIM="@";
extern const string DELIMITER=";";
extern const string EQUAL_SIGN="=";
extern const string ORIGIN="origin";
extern const string VOID="void";
extern const string ZERO="0";
extern const vector<string> OPERATORS={POWER, DIVIDE, MULTIPLY, ADD};
extern const int OPERATORS_SIZE=OPERATORS.size();
