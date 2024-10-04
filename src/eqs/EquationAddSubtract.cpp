/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "../types/Csv.h"
#include "../types/AddSubtract.h"
#include "../inc/namespace.h"
#include <cstdint>

using namespace libremcm;

const string EMPTY=" ";

const vector<string> GetUp(const vector<string> v, uint16_t i)
{
  vector<string> r;

  while(i>0)
    {
      if(v[i]!=EMPTY) r.emplace_back(v[i]);
      i--;
    }
  return r;
}

const vector<string> GetDown(const vector<string> v, uint16_t i)
{
  vector<string> r;

  for(i=i+1; i<v.size(); i++) if(v[i]!=EMPTY) r.emplace_back(v[i]);
  return r;
}

const AddSubtract GetEquations(const Csv &csv, const uint16_t i)
{
  const vector<string> column=csv.columns[i];
  const vector<string> row=csv.rows[i];
  const vector<string> add_up=GetUp(column, i);
  const vector<string> add_down=GetDown(column, i);
  const vector<string> subtract_right=GetUp(row, i);
  const vector<string> subtract_left=GetDown(row, i);

  vector<string> add_total;
  add_total.reserve(add_up.size()+add_down.size());
  vector<string> subtract_total;
  subtract_total.reserve(subtract_right.size()+subtract_left.size());

  add_total.insert(add_total.end(), add_down.begin(), add_down.end());
  add_total.insert(add_total.end(), add_up.begin(), add_up.end());
  subtract_total.insert(subtract_total.end(), subtract_right.begin(), subtract_right.end());
  subtract_total.insert(subtract_total.end(), subtract_left.begin(), subtract_left.end());
  return {add_total, subtract_total};
}

Map<string, AddSubtract> EquationAddSubtract(const Csv &csv)
{
  Map<string, AddSubtract> Map;
  for(uint16_t i=0; i<csv.diagonal.size(); i++) Map[csv.diagonal[i]]=GetEquations(csv, i);
  return Map;
}
