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

using namespace libremcm;

const string EMPTY=" ";

vector<string> GetUp(const vector<string> &v, int i)
{
  vector<string> r;
  for(i=i-1; i>=0; i--) if(v[i]!=EMPTY) r.emplace_back(v[i]);
  return r;
}

vector<string> GetDown(const vector<string> &v, unsigned int i)
{
  vector<string> r;
  for(i=i+1; i<v.size(); i++) if(v[i]!=EMPTY) r.emplace_back(v[i]);
  return r;
}

AddSubtract GetEquations(const Csv &csv, const int &j)
{
  const vector<string> column=csv.columns[j];
  const vector<string> row=csv.rows[j];
  const vector<string> add_up=GetUp(column, j);
  const vector<string> add_down=GetDown(column, j);
  const vector<string> subtract_right=GetUp(row, j);
  const vector<string> subtract_left=GetDown(row, j);

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

map<string, AddSubtract> EquationAddSubtract(const Csv &csv)
{
  map<string, AddSubtract> map;
  for(unsigned int i=0; i<csv.diagonal.size(); i++) map[csv.diagonal[i]]=GetEquations(csv, i);
  return map;
}
