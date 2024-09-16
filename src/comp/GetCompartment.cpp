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
#include <algorithm>
#include <fstream>
#include <iostream>

using std::cout;
using std::ifstream;

const char DELIMITER=';';
const string EMPTY=" ";

string UpdateValue(const string &str)
{
  const unsigned size=str.size();
  string r=EMPTY;
  if(str.back()==DELIMITER and size>1) r=str.substr(0, size-1);
  return r;
}

vector<string> LineToVector(string &s)
{
  bool end=false;
  unsigned size=s.size();
  unsigned size2;
  unsigned delimiter_i;
  vector<string> r;
  string str;

  while(!end)
     {
       size2=s.size();
       delimiter_i=std::distance(s.begin(), std::find(s.begin(), s.end(), DELIMITER));

       if(size==0)
	 {
	   r.emplace_back(EMPTY);
	   end=true;
	   continue;
	 }
       else if(delimiter_i==size2)
	 {
	   r.emplace_back(s);
	   break;
	 }

       str=s.substr(0, delimiter_i+1);
       s=s.substr(delimiter_i+1, size);
       size=s.size();
       r.emplace_back(UpdateValue(str));
     }
   return r;
}

Csv GetCompartment(ifstream &f)
{
  string line;
  Csv csv;

  while(getline(f, line)) csv.AddCsv(LineToVector(line));
  cout<<" "<<'\n';
  return csv;
}
