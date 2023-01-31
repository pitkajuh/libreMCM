/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <iostream>
#include <vector>
#include "../global/global.h"

using namespace std;

void print_vector2(vector<string> vec)
{
  int i=0;
  string empty="";

  if(vec.size()>0)
    {
      while(i<=vec.size()-1)
	{
	  if(i==0)
	    {
	      empty=vec[i];
	    }
	  else
	    {
	      empty=empty+delimiter+vec[i];
	    }
	  i++;
	}
      cout<<empty<<endl;
    }
}

void print_vector(vector<string> vec)
{
  int i=0;
  string empty="";

  if(vec.size()>0)
    {
      while(i<=vec.size()-1)
	{
	  empty=empty+vec[i];
	  i++;
	}
      cout<<empty<<endl;
    }
}

void print_vector_int(vector<int> vec)
{
  int i=0;
  string empty="";

  while(i<=vec.size()-1)
    {
      if (i==0)
	{
	  empty=to_string(vec[i]);
	}
      else
	{
	  empty=empty+", "+to_string(vec[i]);
	}
      i++;
    }
  cout<<empty<<endl;
}

void vector_print_all(vector<vector<string>> vec)
{
  int i=0, j=0;
  string empty="";

  if(vec.size()>=1)
    {
      cout<<"#=#=#=#=#=#=vector_print_all start#=#=#=#=#=#=#=#="<<endl;

      while(i<=vec.size()-1)
	{
	  while(j<=vec[i].size()-1)
	    {
	      empty=delimiter+empty+vec[i][j]+delimiter;
	      j++;
	    }
	  cout<<empty<<endl;
	  empty="";
	  j=0;
	  i++;
	}
      cout<<"#=#=#=#=#=#=vector_print_all end#=#=#=#=#=#=#=#="<<endl;
    }
}

void vector_print_print_all(vector<vector<vector<string>>> vec)
{
  int i=0, j=0, k=0;
  string empty="";

  if(vec.size()>=1)
    {
      cout<<"#=#=#=#=#=#=vector_print_print_all start#=#=#=#=#=#=#=#="<<endl;

      while(i<=vec.size()-1)
	{
	  while(j<=vec[i].size()-1)
	    {
	      while(k<=vec[i][j].size()-1)
		{
		  empty=empty+vec[i][j][k];
		  k++;
		}
	      k=0;
	      j++;
	      cout<<empty<<endl;
	      empty="";
	    }
	  j=0;
	  i++;
	}
      cout<<"#=#=#=#=#=#=vector_print_print_all end#=#=#=#=#=#=#=#="<<endl;
    }
}
