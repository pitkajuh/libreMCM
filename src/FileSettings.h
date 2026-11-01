#ifndef FILESETTINGS_H
#define FILESETTINGS_H

#include "File.h"

class FileSettings: public File
{
protected:
  streampos SA(ifstream &file, streampos from, const string &line);
public:
  map<uint16_t, string> set;
  map<string, uint16_t> settingsNames;
  double GetSetting(const string &setting);
  double GetTimeStart();
  double GetTimeEnd();
  double GetStepSize();
  FileSettings(const string &fileName);
  FileSettings(){}
  ~FileSettings(){}
};

#endif
