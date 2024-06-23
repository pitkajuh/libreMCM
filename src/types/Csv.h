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
  vector<Row> rows;
  vector<Column> columns;
  vector<string> diagonal;

  void GetDiagonal()
  {
    string compartment;

    for(unsigned int i=0; i<rows.size(); i++)
      {
	compartment=rows[i][i];
	// TODO Check that diagonal element is not empty.
	if(compartment!="void" or compartment!="origin") diagonal.emplace_back(compartment);
      }
  }

  vector<string> GetColumn(const unsigned int &i) const
  {
    vector<string> c;
    for(unsigned int j=0; j<columns.size(); j++) c.emplace_back(columns[i][j]);
    return c;
  }

  void PrintColumn() const
  {
    for(unsigned int i=0;i<columns.size(); i++) GetColumn(i);
  }

  void UpdateColumns(const vector<string> &row)
  {
    const Column c={};
    while(columns.size()!=row.size()) columns.emplace_back(c);
    // TODO:  Add error check here, which checks that the there are an equal amount of rows and columns i.e. csv is symmetrical.
  }

  void CreateColumn(const vector<string> &row)
  {
    UpdateColumns(row);
    for(unsigned int i=0; i<row.size(); i++) columns[i].emplace_back(row[i]);
  }

  void AddCsv(const vector<string> &row)
  {
    rows.emplace_back(row);
    CreateColumn(row);
  }
};

#endif
