/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef FILESETTINGS_H
#define FILESETTINGS_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <map>
#include "File.h"

using std::map;
using std::cout;
using std::vector;
using std::pair;
using std::streampos;
using std::ifstream;

class FileSettings: public File
{
protected:
  streampos SA(ifstream &file, streampos from, const string &line);
public:
  map<string, string> set;

  FileSettings(const string &fileName);
  FileSettings(){}
  ~FileSettings(){}
};



#endif
