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
      const uint16_t at=iv.find("=");
      name=iv.substr(0, at);
      value=std::stod(iv.substr(at+1, iv.size()-1));
      // initialValueNames.insert(name);
      result[name]=value;
    }
  return result;
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
      const EdgeStruct edge{strs[0], strs[1], strs[2]};
      edges.emplace_back(edge);
    }
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
      CreateEdges(result.second);
    }
  from=result.first;
  return from;
}


void FileGraph::InitResults(double *&results, const uint16_t timeStart)
{
  // N=1+n*(1+nx*ny);
  // results=new double[N];
  // results[0]=timeStart;

  // unsigned i=1;

  // for(auto &[name, value]: all)
  //   {
  //     for(const auto&[v1, v2]: value)
  // 	{
  // 	  results[i]=v2;
  // 	  i++;
  // 	}
  //   }

  // all.clear();

  // for(unsigned i=0; i<n*nx; i++)
  //   {
  //     cout<<"i="<<i<<" "<<results[i]<<'\n';
  //   }
}

FileGraph::FileGraph(const string &fileName, const unsigned uint16_t, const uint16_t timeEnd, const uint16_t stepSize)
{
  ny=(timeEnd-timeStart)/stepSize;
  ReadFile(fileName);


  // for(auto &[name, value]: all)
  //   {
  //     for(const string &v: initialValueNames)
  // 	{
  // 	  value[v];
  // 	}
  //   }

  // nx=initialValueNames.size();
  n=all.size();
}
