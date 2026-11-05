#ifndef FILESETTINGS_H
#define FILESETTINGS_H

#include "File.h"

class FileSettings: public File
{
protected:
  streampos SA(ifstream &file, streampos from, const string &line);
public:
  double timeStart;
  double timeEnd;
  double stepSize;
  map<uint16_t, string> set;
  map<string, uint16_t> settingsNames;
  void Read(const string &fileName);
  double GetSetting(const string &setting);
  double GetTimeStart();
  double GetTimeEnd();
  double GetStepSize();
  double SetTimeStart();
  double SetTimeEnd();
  double SetStepSize();
  FileSettings(){}
  ~FileSettings(){}
};

#endif
