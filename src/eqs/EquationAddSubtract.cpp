/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <unordered_map>
#include "../types/Csv.h"

using std::unordered_map;

#include <iostream>
using std::cout;

const string EMPTY=" ";

struct AddSubtract
{
  vector<string> add;
  vector<string> subtract;

  AddSubtract(const vector<string> v1, const vector<string> v2)
  {
    add=v1;
    subtract=v2;
  }
};

vector<string> GetUp(const vector<string> v, int i)
{
  vector<string> r;
  for(i=i-1; i>=0; i--)  if(v[i]!=EMPTY) r.push_back(v[i]);
  return r;
}

vector<string> GetDown(const vector<string> v, int i)
{
  vector<string> r;
  for(i=i+1; i<v.size(); i++) if(v[i]!=EMPTY)  r.push_back(v[i]);
  return r;
}

AddSubtract GetEquations(const unordered_map<string, string> equations_map, const Csv csv, const int j)
{
  const vector<string> column=csv.GetColumn(j);
  const vector<string> row=csv.rows[j];
  const vector<string> add_up=GetUp(column, j);
  const vector<string> add_down=GetDown(column, j);
  const vector<string> subtract_up=GetUp(row, j);
  const vector<string> subtract_down=GetDown(row, j);

  vector<string> add_total;
  vector<string> subtract_total;
  add_total.insert(add_up.end(), add_down.begin(), add_down.end());
  add_total.insert(subtract_up.end(), subtract_down.begin(), subtract_down.end());
  AddSubtract r(add_total, subtract_total);
  return r;
}

void EquationAddSubtract(const unordered_map<string, string> equations_map, const Csv csv)
{
  for(int i=0; i<csv.diagonal.size(); i++)
    {
      GetEquations(equations_map, csv, i);
    }
}
