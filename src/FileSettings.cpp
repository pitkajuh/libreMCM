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

double FileSettings::SetTimeStart()
{
  return GetSetting("time_start");
}

double FileSettings::SetTimeEnd()
{
  return GetSetting("time_end");
}

double FileSettings::SetStepSize()
{
  return GetSetting("step_size");
}

double FileSettings::GetTimeStart()
{
  return timeStart;
}

double FileSettings::GetTimeEnd()
{
  return timeEnd;
}

double FileSettings::GetStepSize()
{
  return stepSize;
}

void FileSettings::Read(const string &fileName)
{
  ReadFile(fileName);
  timeStart=SetTimeStart();

  if(timeStart<0) throw std::invalid_argument("Starting time cannot be negative");
  timeEnd=SetTimeEnd();

  if(timeEnd<0) throw std::invalid_argument("Ending time cannot be negative");
  if(timeStart>timeEnd) throw std::invalid_argument("Starting time is larger than ending time");

  stepSize=SetStepSize();
  if(stepSize==0) throw std::invalid_argument("Step size cannot be zero");
  if(stepSize>=timeEnd) throw std::invalid_argument("Step size is too large.");
  // Get other parameters here before clearing.
  // Get algorithm type, e.g. RK4
  set.clear();
}
