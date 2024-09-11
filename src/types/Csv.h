/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef CSVCLASS_H
#define CSVCLASS_H

#include <string>
#include <vector>

using std::string;
using std::vector;
#include <iostream>
using std::cout;

using Column=vector<string>;
using Row=vector<string>;

class Csv
{
public:
  int size=0;
  vector<Row> rows;
  vector<Column> columns;
  vector<string> diagonal;

  void SetSize(const vector<string> &row)
  {
    if(size==0 or row.size()==size)
      {
	size=row.size();
      }
    else if(row.size()<2)
      {
	// Error, not enough rows/columns!
      }
    else
      {
	// Error, not symmetrical!
      }
  }

  void GetDiagonal()
  {
    string compartment;

    for(unsigned i=0; i<rows.size(); i++)
      {
	compartment=rows[i][i];
	// TODO Check that diagonal element is not empty.
	if(compartment!="void" or compartment!="origin") diagonal.emplace_back(compartment);
      }
  }

  void UpdateColumns(const vector<string> &row)
  {
    const Column c(size);
    while(columns.size()!=row.size()) columns.emplace_back(c);
  }

  void CreateColumn(const vector<string> &row)
  {
    SetSize(row);
    UpdateColumns(row);
    for(unsigned i=0; i<row.size(); i++) columns[i][i]=row[i];
  }

  void AddCsv(const vector<string> &row)
  {
    SetSize(row);
    rows.emplace_back(row);
    CreateColumn(row);
  }
};

#endif
