#include "FileSettings.h"

streampos FileSettings::SA(ifstream &file, streampos from, const string &line)
{
  pair<streampos, vector<string>> result;
  const string settings="simulation_settings";

  if(line.substr(0, 19)==settings)
    {
      result=ReadContent(file, from, settings, 19);
      set=GetSettings(result.second, settingsNames);
    }
  from=result.first;
  return from;
}

double FileSettings::GetSetting(const string &setting)
{
  // TODO. Do something if variable setting is not found.
  auto aa=set[settingsNames[setting]];
  return std::stod(aa);
}

double FileSettings::GetTimeStart()
{
  return GetSetting("time_start");
}

double FileSettings::GetTimeEnd()
{
  return GetSetting("time_end");
}

double FileSettings::GetStepSize()
{
  return GetSetting("step_size");
}

FileSettings::FileSettings(const string &fileName)
{
  ReadFile(fileName);
}
