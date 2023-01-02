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
#include "global.h"
#include "numerical_calculation.h"

using namespace std;

void write_to_file()
{
  int i=0;
  int j=0;
  int k=0;
  double t=0;
  string str;
  string compartment_name;
  vector<tuple<string, vector<string>>> parameters_data;
  tuple<string, vector<string>> parameter;
  string parameter_name;
  vector<string> parameter_values;
  bool ready=false;
  string parameter_values_k;
  tuple<
    string, // compartment name
    vector<
      tuple<
	string, // parameter name
	vector<
	  string // parameter values
	  >
	>     >      >
    params_graph_up_i;
  const string empty_str="";
  const string str_new_row="\n";
  const string file_type=".txt";
  string t_str;

  while(i<=params_graph_up.size()-1)
    {
      params_graph_up_i=params_graph_up[i];
      compartment_name=get<0>(params_graph_up_i);
      parameters_data=get<1>(params_graph_up_i);
      // cout<<"############## compartment name "<<compartment_name<<" ##############"<<endl;
      ofstream myfile (compartment_name+file_type);

      // while(j<=parameters_data.size()-1)
      while(!ready)
	{
	  parameter=parameters_data[j];
	  parameter_name=get<0>(parameter);
	  parameter_values=get<1>(parameter);
	  parameter_values_k=parameter_values[k];
	  // cout<<parameter_values.size()-1<<endl;
	  // cout<<"############## parameter name "<<parameter_name<<" ##############"<<" "<<parameter_values.size()-1<<endl;

	  if(k==parameter_values.size()-1)
	    {
	      ready=true;
	    }
	  else if(parameters_data.size()-1==0)
	    {
	      // cout<<"len=0"<<endl;
	      // cout<<k<<" "<<j<<"/"<<parameters_data.size()-1<<endl;
	      t_str=to_string(t);
	      str=str+t_str+delimiter+parameter_values_k;
	      str=str+str_new_row;
	      k++;
	      t=t+h;
	      // cout<<str<<endl;
	      // continue;
	      // break;
	    }
	  else if(j==0 and parameters_data.size()-1!=0)
	    {
	      // cout<<"j=0"<<endl;
	      // k++;
	      // cout<<k<<" "<<j<<"/"<<parameters_data.size()-1<<endl;
	      t_str=to_string(t);
	      str=str+t_str+delimiter+parameter_values_k+delimiter;
	      // cout<<str<<endl;
	      // cout<<"##########"<<endl;
	      j++;
	    }
	  else if(j==parameters_data.size()-1)
	    {
	      // cout<<"j==parameters_data.size()-1"<<endl;
	      str=str+parameter_values_k;
	      // cout<<k<<" "<<j<<"/"<<parameters_data.size()-1<<endl;
	      // cout<<str<<endl;
	      str=str+str_new_row;
	      j=0;
	      k++;
	      t=t+h;
	      // cout<<"##########"<<endl;
	      continue;
	    }
	  else
	    {
	      // cout<<"else"<<endl;
	      // cout<<k<<" "<<j<<"/"<<parameters_data.size()-1<<endl;
	      str=str+parameter_values_k+delimiter;
	      // cout<<str<<endl;
	      // cout<<"##########"<<endl;
	      j++;
	    }
	  // cout<<"increase j"<<endl;
	  // j++;
	  //	  t=t+h;
	}

      ready=false;
      myfile<<str;
      str=empty_str;
      myfile.close();
      j=0;
      k=0;
      t=0;
      i++;
    }
}
