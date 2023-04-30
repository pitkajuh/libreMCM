/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef INDICEOPERATORSDATA_H
#define INDICEOPERATORSDATA_H

#include "IndiceOperatorData.h"
#include <vector>

using std::vector;

class IndiceOperatorsData
{
public:
  vector<vector<IndiceOperatorData>> indice_data;

  void push_back(const vector<IndiceOperatorData> ind_data)
  {
    indice_data.push_back(ind_data);
  }
  void clear()
  {
    indice_data.clear();
  }
  int size()
  {
    int size=indice_data.size();
    return size;
  }
  vector<IndiceOperatorData>& operator[](const int i)
  {
    return indice_data[i];
  }
  const vector<IndiceOperatorData>& operator[](const int i) const
  {
    return indice_data[i];
  }
};

#endif
