/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef ADDSUBTRACT_H
#define ADDSUBTRACT_H

struct AddSubtract
{
  vector<string> add;
  vector<string> subtract;

  AddSubtract(){}
  AddSubtract(const vector<string> &v1, const vector<string> &v2)
  {
    add=v1;
    subtract=v2;
  }
};

#endif
