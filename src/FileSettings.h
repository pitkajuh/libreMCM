#ifndef FILESETTINGS_H
#define FILESETTINGS_H

#include "File.h"

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
