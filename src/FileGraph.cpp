#include "FileGraph.h"

string FileGraph::GetVertexName(string line)
{
  line.erase(line.begin(), line.begin()+6);

  if(line.back()=='{') line.erase(line.end()-1);

  return line;
}

map<string, double> FileGraph::SetInitialValueName(const vector<string> &ivs)
{
  string name;
  double value;
  map<string, double> result;

  for(const auto &iv: ivs)
    {
      const unsigned at=iv.find("=");
      name=iv.substr(0, at);
      value=std::stod(iv.substr(at+1, iv.size()-1));
      initialValueNames.insert(name);
      result[name]=value;
    }
  return result;
}

streampos FileGraph::SA(ifstream &file, streampos from, const string &line)
{
  pair<streampos, vector<string>> result;
  string vertexName;
  const string vertex="vertex";
  const string edges="edges";

  if(line.substr(0, 6)==vertex)
    {
      vertexName=GetVertexName(line);
      vertexNames.emplace_back(vertexName);
      result=ReadContent(file, from, vertex, 6);
      all[vertexName]=SetInitialValueName(result.second);
    }
  else if(line.substr(0, 5)==edges)
    {
      result=ReadContent(file, from, edges, 5);
    }
  from=result.first;
  return from;
}


void FileGraph::InitResults(double *&results, const unsigned timeStart)
{
  N=1+n*(1+nx*ny);
  results=new double[N];
  results[0]=timeStart;

  unsigned i=1;

  for(auto &[name, value]: all)
    {
      for(const auto&[v1, v2]: value)
	{
	  results[i]=v2;
	  i++;
	}
    }

  all.clear();

  for(unsigned i=0; i<n*nx; i++)
    {
      cout<<"i="<<i<<" "<<results[i]<<'\n';
    }
}

FileGraph::FileGraph(const string &fileName, const unsigned timeStart, const unsigned timeEnd, const unsigned stepSize)
{
  ny=(timeEnd-timeStart)/stepSize;
  ReadFile(fileName);


  for(auto &[name, value]: all)
    {
      for(const string &v: initialValueNames)
	{
	  value[v];
	}
    }

  nx=initialValueNames.size();
  n=all.size();
}
