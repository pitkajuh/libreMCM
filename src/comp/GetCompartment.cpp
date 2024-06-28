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
using std::find;
using std::distance;

const char DELIMITER=';';
const string EMPTY=" ";

string UpdateValue(const string &str)
{
  const int size=str.size();
  string r=EMPTY;
  if(str.back()==DELIMITER and size>1) r=str.substr(0, size-1);
  return r;
}

vector<string> LineToVector(string &s)
{
  bool end=false;
  unsigned int size=s.size();
  unsigned int size2;
  unsigned int delimiter_i;
  vector<string> r;
  string str;

  while(!end)
     {
       size2=s.size();
       delimiter_i=distance(s.begin(), find(s.begin(), s.end(), DELIMITER));

       if(size==0)
	 {
	   r.emplace_back(EMPTY);
	   // cout<<"s1: "<<": "<<size<<" "<<size2<<" "<<delimiter_i<<'\n';
	   end=true;
	   continue;
	 }
       else if(delimiter_i==size2)
	 {
	   r.emplace_back(s);
	   // cout<<"s2:"<<s<<": "<<size<<" "<<size2<<" "<<delimiter_i<<'\n';
	   break;
	 }

       str=s.substr(0, delimiter_i+1);
       s=s.substr(delimiter_i+1, size);
       size=s.size();
       r.emplace_back(UpdateValue(str));
       // cout<<"s :"<<s<<":"<<size<<" "<<size2<<" "<<delimiter_i<<'\n';
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
