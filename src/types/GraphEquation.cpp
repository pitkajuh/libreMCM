#include "Vertex.h"
#include "Graph.h"

bool GraphEquation::IsInMap(const string &s){return vmap.count(s)>0;}

void GraphEquation::AddToMap(Vertex *v, const string &s)
{
  if(!IsInMap(s)) vmap[s]=v;
  else cout<<"AA "<<vmap[s]<<'\n';
}
