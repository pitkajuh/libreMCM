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
#include<limits>

// #include <cmath>

using std::string;
using std::vector;
using std::numeric_limits;

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
extern const string COMMA=",";
extern const string MATH_OP_PREFIX="mcm.";
extern const string SIN_I="sin";
extern const string COS_I="cos";
extern const string POWER2_I="power";
extern const string EXP_I="exp";
extern const string LOG_I="log";
extern const string SQRT_I="sqrt";
extern const string PI_I="pi";
extern const string SIN=MATH_OP_PREFIX+SIN_I;
extern const string COS=MATH_OP_PREFIX+COS_I;
extern const string POWER2=MATH_OP_PREFIX+POWER2_I;
extern const string EXP=MATH_OP_PREFIX+EXP_I;
extern const string LOG=MATH_OP_PREFIX+LOG_I;
extern const string SQRT=MATH_OP_PREFIX+SQRT_I;
extern const vector<string> OPERATORS={DIVIDE, MULTIPLY, ADD};
extern const int OPERATORS_SIZE=OPERATORS.size();
extern const string MATH="math";
extern const string TRIG="trig";
extern const string PI=MATH_OP_PREFIX+PI_I;
extern const double INF=numeric_limits<double>::infinity();
extern const double NEG_INF=-1*INF;
