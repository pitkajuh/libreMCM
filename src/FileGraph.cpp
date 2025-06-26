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

void FileGraph::CreateEdge(map<string, uint16_t> &equationNames, Equations &equations, const vector<uint16_t> &noivs, const vector<uint16_t> &noOfInitialValue)
{
  cout<<" "<<'\n';
  // Edge2 e;

  for(const auto &[i, j]: vertexEquationsAddSubtract)
    {
      // Edge2 e(j.first.size(), j.second.size());
      cout<<"Vertex "<<i<<" "<<j.first.size()<<" "<<j.second.size()<<'\n';
      Edge2 e;
      e.Create(j.first.size(), j.second.size());

      uint16_t l=0;

      for(const auto &equationName: j.first)
	{
	  cout<<"Add "<<equationName<<'\n';
	  e.equationAdd.emplace_back(equations.equations[equationNames[equationName]]);
	  l++;
	}

      l=0;

      for(const auto &equationName: j.second)
	{
	  cout<<"Subtract "<<equationName<<'\n';
	  e.equationSubtract.emplace_back(equations.equations[equationNames[equationName]]);
	  l++;
	}

      edgesNew2.emplace_back(e);

      // for(const auto &k: j.second)
      // 	{
      // 	  cout<<"Subtract "<<k<<'\n';
      // 	}
    }
  cout<<" "<<'\n';


  // std::set<std::pair<uint16_t, uint16_t>> aa;
  // for(const auto &[name, id]: vertexNamesMap)
  //   {
  //     cout<<"Find "<<name<<'\n';
  //     int i=0;
  //     for(const auto &edge: edges)
  // 	{
  // 	  // auto from=edge.from;
  // 	  cout<<i<<" "<<edge.from<<" "<<edge.to<<" "<<edge.equationName<<'\n';
  // 	  // if(name==from) cout<<"FOUND from "<<name<<" "<<edge.equationName<<'\n';
  // 	  i++;
  // 	}

  //     // for(const auto &edge: edges)
  //     // 	{
  //     // 	  auto to=edge.to;

  //     // 	  if(name==to) cout<<"to "<<name<<'\n';
  //     // 	}
  //     cout<<" "<<'\n';
  //   }
  // for(const auto &edge: edges)
  //   {
  //     Edge e(&equations.equations[equationNames[edge.equationName]], vertexNamesMap[edge.from], vertexNamesMap[edge.to], noivs, noOfInitialValue);
  //     edgesNew.emplace_back(e);
  //     // aa.insert(e.p1);
  //     // aa.insert(e.p2);
  //   }
  // // cout<<aa.size()<<'\n';
  // // for(const auto &i: aa){cout<<"AA "<<i.first<<" "<<i.second<<'\n';}
  // edges.clear();
}

void FileGraph::CreateEdges(const vector<string> &v)
{
  cout<<vertexNamesMap.size()<<'\n';
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

      if(strs[1]==sink) hasSink=1;
      if(strs[0]==source) hasSource=1;
      // if(strs[0]==source) edge.from=edge.to;
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

  for(uint16_t i=0; i<N; i++)
    {
      results[i]=0;
    }

  for(auto &[name, value]: all)
    {
      for(const auto&[v1, v2]: value)
	{
	  results[i]=v2;
	  i++;
	}
    }

  all.clear();

  // The values of sink (several zeros) are also added to
  // the results as initial values.
  if(hasSink)
    {
      for(auto &[name, value]: sinkMap)
	{
	  for(const auto&[v1, v2]: value)
	    {
	      results[i]=v2;
	      i++;
	    }
	}
      sinkMap.clear();
    }

  // for(unsigned i=0; i<nx; i++)
  //   {
  //     cout<<"i="<<i<<" "<<results[i]<<'\n';
  //   }
}

void FileGraph::InitInitialValues()
{
  // Initialize the initial values for each vertex according to edges of
  // the graph. For example, if vertex A={a1=10, a2=20} is connected to
  // vertex B={b1=5, b2=2}, initial values a1 and a2 must be initialized
  // with value of zero in B, so B={a1=0, a2=0 b1=5, b2=2}. Same logic applies
  // when vertex is either sink or source.
  for(const auto &edge: edges)
    {
      // Initialize the values to zero for sink vertex. Sink has an infinite
      // amount of space, so any amount of quantity can be deposited to it.
      if(edge.to==sink)
	{
	  for(const auto &[name, value]: all[edge.from])
	    {
	      sinkMap[sink][name];
	    }
	}

      // Initialize values for vertices, other than sink and source.
      if(edge.from!=source and edge.to!=sink)
	{
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
      noivs.emplace_back(j.size());
      nx+=j.size();
      cout<<"nx "<<nx<<" "<<j.size()<<'\n';
    }

  // for(const auto &[i, j]: sinkMap)
  //   {
  //     noOfInitialValue.emplace_back(noOfInitialValue.back()+j.size());
  //     noivs.emplace_back(j.size());
  //     nx+=j.size();
  //     cout<<"nx "<<nx<<'\n';
  //   }
  cout<<"nx "<<nx<<'\n';
  uint16_t n=0;

  for(const string &name: vertexNames)
    {
      vertexNamesMap[name]=n;
      n++;
    }

  vertexNames.clear();

  if(hasSink) vertexNamesMap[sink]=n;
}
