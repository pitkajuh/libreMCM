/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef COMPARTMENT_H
#define COMPARTMENT_H

#include <unordered_map>
/* #include "Equation.h" */

using std::unordered_map;
using InitialValues=unordered_map<string, string>;

class Compartment
{
public:
  vector<string> equations_add;
  vector<string> equations_subtract;
  InitialValues ivs;
/*   vector<string> initial_values; */
/*   //equations add */
/*   //equations subtract */
/*   //equation total (combine add and subtract) */
/* public: */
/*   string name; */
};

/* class Void: public Compartment */
/* { */
/* public: */

/* }; */

/* class Origin: public Compartment */
/* { */
/* public: */

/* }; */


#endif
