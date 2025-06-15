#include <cstdint>
#include <limits>
#include "FileGraph.h"
#include "GraphEquation.h"
#include "Edge.h"

string FileGraph::GetVertexName(string line)
{
  line.erase(line.begin(), line.begin()+6);

  if(line.back()=='{') line.erase(line.end()-1);

  return line;
}

map<string, double> FileGraph::SetInitialValueName(vector<string> &ivs)
{
  map<string, double> result;

  for(auto &iv: ivs)
    {
      const uint16_t at=iv.find("=");
      const string name=iv.substr(0, at);
      iv.erase(iv.begin(), iv.begin()+at+1);
      result[name]=std::stod(iv);
    }
  return result;
}

void FileGraph::CreateEdge(map<string, uint16_t> &equationNames, Equations &equations)
{
  for(const auto &edge: edges)
    {
      cout<<edge.from<<" "<<edge.to<<'\n';
      Edge e(&equations.equations[equationNames[edge.equationName]], vertexNamesMap[edge.from], vertexNamesMap[edge.to]);
    }
  edges.clear();
}

void FileGraph::CreateEdges(const vector<string> &v)
{
  for(string str: v)
    {
      string strs[3];
      uint8_t i=0;

      while(str.size()>1)
	{
	  const uint16_t at=str.find(",");

	  if(at>=str.size())
	    {
	      strs[i]=str;
	      break;
	    }

	  strs[i]=str.substr(0, at);
	  str.erase(str.begin(), str.begin()+at+1);
	  i++;
	}
      cout<<strs[0]<<" "<<strs[1]<<" "<<strs[2]<<'\n';
      if(strs[0]=="source") hasSource=1;
      if(strs[1]=="sink") hasSink=1;
      const EdgeStruct edge{strs[0], strs[1], strs[2]};
      edges.emplace_back(edge);
    }
}

streampos FileGraph::SA(ifstream &file, streampos from, const string &line)
{
  pair<streampos, vector<string>> result;
  const string vertex="vertex";
  const string edges="edges";

  if(line.substr(0, 6)==vertex)
    {
      const string vertexName=GetVertexName(line);
      vertexNames.insert(vertexName);
      result=ReadContent(file, from, vertex, 6);
      all[vertexName]=SetInitialValueName(result.second);
    }
  else if(line.substr(0, 5)==edges)
    {
      result=ReadContent(file, from, edges, 5);
      CreateEdges(result.second);
    }
  from=result.first;
  return from;
}

void FileGraph::InitResults(double *&results)
{
  N=nx*ny;
  results=new double[N];
  uint16_t i=0;

  for(auto &[name, value]: all)
    {
      for(const auto&[v1, v2]: value)
	{
	  results[i]=v2;
	  i++;
	}
    }

  all.clear();
  cout<<"ALL cleared"<<'\n';
  for(unsigned i=0; i<nx; i++)
    {
      cout<<"i="<<i<<" "<<results[i]<<'\n';
    }
}

void FileGraph::InitInitialValues(const string &vertex)
{
  for(const auto &edge: edges)
    {
      if(edge.to==vertex)
	{
	  for(const auto &[name, value]: all[edge.from])
	    {
	      cout<<vertex<<" "<<name<<" "<<value<<'\n';
	      all[vertex][name];
	    }
	}
      if(edge.from==vertex)
	{
	  for(const auto &[name, value]: all[edge.to])
	    {
	      cout<<vertex<<" "<<name<<'\n';
	      // if(edge.from=="source") all["source"][name]=std::numeric_limits<double>::max();
	      if(edge.from=="source") all["source"][name]=std::numeric_limits<double>::infinity();

	      else all[vertex][name];
	    }
	}
      cout<<" "<<'\n';
    }
}

FileGraph::FileGraph(const string &fileName, const uint16_t timeStart, const uint16_t timeEnd, const uint16_t stepSize)
{
  ny=(timeEnd-timeStart)/stepSize;
  ReadFile(fileName);

  for(auto &[name, value]: all)
    {
      cout<<"NAME "<<name<<'\n';
      InitInitialValues(name);
      noOfInitialValue.emplace_back(value.size()+nx);
      nx+=value.size();
    }

  cout<<"Now "<<'\n';

  for(auto &i: noOfInitialValue)
    {
      cout<<i<<'\n';
    }

  uint16_t n=0;

  for(const string &name: vertexNames)
    {
      vertexNamesMap[name]=n;
      cout<<"NAME "<<name<<" "<<n<<'\n';
      n++;
    }

  if(hasSink and hasSource)
    {
      vertexNamesMap["sink"]=n;
      vertexNamesMap["source"]=n+1;
    }
  else if(hasSink) vertexNamesMap["sink"]=n;
  else if(hasSource) vertexNamesMap["source"]=n;

  vertexNames.clear();
}
