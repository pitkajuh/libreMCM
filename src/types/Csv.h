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

  vector<string> GetColumn(const int i) const
  {
    vector<string> c;

    for(int j=0; j<columns.size(); j++) c.push_back(columns[i][j]);

    return c;
  }

  void PrintColumn() const
  {
    for(int i=0;i<columns.size(); i++) GetColumn(i);
  }

  void UpdateColumns(const vector<string> row)
  {
    const Column c={};

    while(columns.size()!=row.size()) columns.push_back(c);

    // TODO:  Add error check here, which checks that the there are an equal amount of rows and columns i.e. csv is symmetrical.
    // cout<<"SIZES "<<rows_size<<" "<<columns_size<<'\n';
  }

  void CreateColumn(const vector<string> row)
  {
    UpdateColumns(row);

    for(int i=0; i<row.size(); i++) columns[i].push_back(row[i]);
  }

  void AddCsv(const vector<string> row)
  {
    rows.push_back(row);
    CreateColumn(row);
  }
};

#endif
