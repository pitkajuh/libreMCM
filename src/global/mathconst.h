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
#include <array>

using std::string;
using std::array;

const string DIVIDE="/";
const string MULTIPLY="*";
const string ADD="+";
const string SUBTRACT="-";
const string OPEN="(";
const string CLOSE=")";
const string EXP="^";
const string BOPEN="{";

const array<string, 5> OPERATORS={EXP, DIVIDE, MULTIPLY, ADD, SUBTRACT};
const array<string, 7> OPERATORS2={EXP, DIVIDE, MULTIPLY, ADD, SUBTRACT, OPEN, CLOSE};

#endif
