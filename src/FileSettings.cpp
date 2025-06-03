#include "FileSettings.h"

streampos FileSettings::SA(ifstream &file, streampos from, const string &line)
{
  pair<streampos, vector<string>> result;
  const string settings="simulation_settings";

  if(line.substr(0, 19)==settings)
    {
      result=ReadContent(file, from, settings, 19);
      set=GetSettings(result.second);
    }
  from=result.first;
  return from;
}

FileSettings::FileSettings(const string &fileName)
{
  ReadFile(fileName);
}
