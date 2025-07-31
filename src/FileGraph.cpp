#include <cstdint>
#include <limits>
#include "FileGraph.h"
#include "Equation.h"
#include "Edge.h"

const string source="source";
const string sink="sink";

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
  for(const auto &[i, j]: vertexEquationsAddSubtract)
    {
      Edge e(j.first.size(), j.second.size());

      for(const auto &equationName: j.first)
	{
	  e.equationsAdd.emplace_back(equations.equations[equationNames[equationName]]);
	}

      for(const auto &equationName: j.second)
	{
	  e.equationsSubtract.emplace_back(equations.equations[equationNames[equationName]]);
	}
      edgesNew2.emplace_back(e);
    }
  vertexEquationsAddSubtract.clear();
}

void FileGraph::CreateEdges(const vector<string> &v)
{
  std::pair<vector<string>, vector<string>> equationsAddSubtract;

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

      EdgeStruct edge{strs[0], strs[1], strs[2]};

      // Add checks here for detecting not allowed edges, e.g. from source to sink, from sink to anything etc.

      // What if same equations adds or subtract twice?
      if(strs[0]!=source) vertexEquationsAddSubtract[strs[0]].second.insert(strs[2]);
      if(strs[1]!=sink) vertexEquationsAddSubtract[strs[1]].first.insert(strs[2]);
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
  // Results from the simulation are added to an array of doubles.
  // The initial values, provided by the user are added to the results
  // because they represent the status of the system at t=timeStart.
  N=nx*ny;
  cout<<"N "<<N<<" "<<nx<<" "<<ny<<'\n';
  results=new double[N];
  uint16_t i=0;
  // uint16_t j=0;

  for(uint16_t i=0; i<N; i++)
    {
      results[i]=0;
    }

  for(auto &[name, value]: all)
    {
      // cout<<name<<'\n';
      for(const auto&[v1, v2]: value)
	{
	  results[i]=v2;
	  // cout<<v1<<" "<<v2<<'\n';
	  i++;
	}
    }



  double *test = new double[nx];
  const uint16_t delta=nx/all.size();
  cout<<"nx "<<nx<<" all "<<all.size()<<" delta "<<delta<<'\n';

  uint16_t j=0;

  // If nx is odd, fix from above where initial values are initialized.
  // cout<<" "<<'\n';
  if(all.size()%2==0)
    {
      // cout<<"even"<<'\n';
      i=1;

      while(i<nx)
	{
	  test[j*all.size()]=results[j];
	  test[i]=results[delta+j];
	  i+=all.size();
	  j++;
	}

      for(uint16_t i=0; i<nx; i++)
	{
	  // cout<<"i="<<i<<" "<<results[i]<<" "<<&results[i]<<'\n';
	  cout<<"i="<<i<<" "<<test[i]<<" "<<&test[i]<<'\n';
	  // results[i]=test[i];
	}
      delete [] test;
    }
  else
    {
      // cout<<"not even"<<'\n';
      i=0;

      // while(i<nx)
      // 	{
      // 	  cout<<j<<" "<<i<<'\n';
      // 	  // cout<<j+all.size()<<" "<<i+1<<'\n';
      // 	  cout<<" "<<'\n';
      // 	  test[j]=results[i];
      // 	  test[j+all.size()]=results[i+1];
      // 	  i+=delta;
      // 	  j++;
      // 	}

      while(i<nx)
	{
	  // cout<<j<<" "<<i<<'\n';
	  // cout<<j+all.size()<<" "<<i+1<<'\n';
	  // cout<<j+all.size()+delta<<" "<<i+2<<'\n';
	  // cout<<j+all.size()<<" "<<i+1<<'\n';
	  // cout<<" "<<'\n';
	  test[j]=results[i];
	  test[j+all.size()]=results[i+1];
	  test[j+all.size()+delta]=results[i+2];
	  i+=delta;
	  j++;
	}

      // for(uint16_t i=0; i<nx; i++)
      // 	{
      // 	  // cout<<"i="<<i<<" "<<results[i]<<" "<<&results[i]<<'\n';
      // 	  cout<<"i="<<i<<" "<<test[i]<<" "<<&test[i]<<'\n';
      // 	}
      delete [] test;
    }
  all.clear();
}

void FileGraph::InitInitialValues()
{
  // Initialize the initial values for each vertex according to edges of
  // the graph. For example, if vertex A={a1=10, a2=20} is connected to
  // vertex B={b1=5, b2=2}, initial values a1 and a2 must be initialized
  // with value of zero in B, so B={a1=0, a2=0 b1=5, b2=2}. Sink and
  // source are skipped

  for(const auto &edge: edges)
    {
      // Initialize values for vertices, other than sink and source.
      if(edge.from!=source and edge.to!=sink)
	{
	  cout<<"size "<<all[edge.to].size()<<" "<<all[edge.from].size()<<'\n';
	  for(const auto &[name, value]: all[edge.to])
	    {
	      all[edge.from][name];
	    }

	  for(const auto &[name, value]: all[edge.from])
	    {
	      all[edge.to][name];
	    }
	}
    }
}

FileGraph::FileGraph(const string &fileName, const uint16_t timeStart, const uint16_t timeEnd, const uint16_t stepSize)
{
  ny=(timeEnd-timeStart)/stepSize;
  ReadFile(fileName);
  InitInitialValues();

  for(auto &[i, j]: all)
    {
      noOfInitialValue.emplace_back(j.size()+nx);
      nx+=j.size();
      cout<<"nx "<<nx<<" "<<j.size()<<'\n';
    }

  uint16_t n=0;

  for(const string &name: vertexNames)
    {
      vertexNamesMap[name]=n;
      n++;
    }
  vertexNames.clear();
}
