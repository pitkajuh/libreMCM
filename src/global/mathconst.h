/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef MATHCONST_H
#define MATHCONST_H

#include <string>
#include <vector>

using std::string;
using std::vector;

const string DIVIDE="/";
const string MULTIPLY="*";
const string ADD="+";
const string SUBTRACT="-";
const string OPEN="(";
const string CLOSE=")";
const string EXP="^";
const string BOPEN="{";

const vector<string> OPERATORS={EXP, DIVIDE, MULTIPLY, ADD, SUBTRACT};
const vector<string> OPERATORS2={EXP, DIVIDE, MULTIPLY, ADD, SUBTRACT, OPEN, CLOSE};

#endif
