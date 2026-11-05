#include <cstdint>
#include <limits>
#include "FileGraph.h"
#include "FileSettings.h"
#include "Equation.h"
#include "Edge.h"
#include "Graph.h"

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

void FileGraph::CreateEdge(Graph &graph, map<string, uint16_t> &equationNames, Equations &equations)
{
  for(const auto &[i, j]: vertexEquationsAddSubtract)
    {
      Edge e(j.first.size(), j.second.size());

      for(const auto &equationName: j.first)
	{
	  e.AddToEquationsAdding(equations.equations[equationNames[equationName]]);
	}

      for(const auto &equationName: j.second)
	{
	  e.AddToEquationsSubtracting(equations.equations[equationNames[equationName]]);
	}
      graph.AddEdge(e);
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

  if(line.substr(0, 6)=="vertex")
    {
      const string vertexName=GetVertexName(line);
      vertexNames.insert(vertexName);
      result=ReadContent(file, from, "vertex", 6);
      vertexInitialValueMap[vertexName]=SetInitialValueName(result.second);
    }
  else if(line.substr(0, 5)=="edges")
    {
      result=ReadContent(file, from, "edges", 5);
      CreateEdges(result.second);
    }
  from=result.first;
  return from;
}

void FileGraph::CreateVertices(Graph &graph, vector<double> &results)
{
  // Results from the simulation are added to an array of doubles.
  // The initial values, provided by the user are added to the results
  // because they represent the status of the system at t=timeStart.
  N=nx*ny;
  results.reserve(N);

  uint16_t j=0;

  for(auto &[name, value]: vertexInitialValueMap)
    {
      for(const auto&[v1, v2]: value)
	{
	  results[j]=v2;
	  j++;
	}
    }

  uint8_t id=0;

  for(auto &[name, value]: vertexInitialValueMap)
    {
      Vertex v(this->N, value.size(), name, id);

      for(const auto &[v1, v2]: value)
	{
	  v.AddValue(v2);
	}
            // std::cout<<"a "<<n<<" "<<name<<'\n';
      graph.AddVertex(v);
      id++;
    }

  uint16_t i=0;

  // If nx is odd, fix from above where initial values are initialized.
  if(nx!=vertexInitialValueMap.size())
    {
      double *test = new double[nx];
      const uint16_t delta=nx/vertexInitialValueMap.size();

      if(vertexInitialValueMap.size()%2==0)
	{
	  i=1;

	  while(i<nx)
	    {
	      test[j*vertexInitialValueMap.size()]=results[j];
	      test[i]=results[delta+j];
	      i+=vertexInitialValueMap.size();
	      j++;
	    }

	  for(uint16_t i1=0; i1<nx; i1++)
	    {
	      results[i1]=test[i1];
	    }
	  delete [] test;
	}
      else
	{
	  i=0;

	  while(i<nx)
	    {
	      test[j]=results[i];
	      test[j+vertexInitialValueMap.size()]=results[i+1];
	      i+=delta;
	      j++;
	    }

	  for(uint16_t i2=0; i2<nx; i2++)
	    {
	      results[i2]=test[i2];
	    }
	  delete [] test;
	}
    }
  vertexInitialValueMap.clear();
}

void FileGraph::CreateGraph(const FileSettings &simulationParameters)
{
  Create(simulationParameters);
  InitInitialValues();
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
	  for(const auto &[name, value]: vertexInitialValueMap[edge.to])
	    {
	      vertexInitialValueMap[edge.from][name];
	    }

	  for(const auto &[name, value]: vertexInitialValueMap[edge.from])
	    {
	      vertexInitialValueMap[edge.to][name];
	    }
	}
    }
}

void FileGraph::Read(const string &fileName)
{
  ReadFile(fileName);
}

void FileGraph::Create(const FileSettings &simulationParameters)
{
  ny=(simulationParameters.timeEnd-simulationParameters.timeStart)/simulationParameters.stepSize;

  for(auto &[i, j]: vertexInitialValueMap)
    {
      noOfInitialValue.emplace_back(j.size());
      nx+=j.size();
    }

  uint16_t n=0;

  for(const string &name: vertexNames)
    {
      std::cout<<"a "<<n<<" "<<name<<'\n';
      vertexNamesMap[name]=n;
      n++;
    }
  vertexNames.clear();
}
