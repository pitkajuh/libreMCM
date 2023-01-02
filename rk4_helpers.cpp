/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <tuple>
#include <string>
#include <vector>
#include "global.h"
#include "values_to_graph.h"
#include "calculate_order_of_operations.h"
#include "replace_in_vector.h"
#include "read_compartment_definition.h"
#include "vector_convert.h"
#include "rk4.h"
#include "string_split.h"
#include "helpers.h"

using namespace std;

int asd=0;

// string get_last_value_loop3(string parameter_name, string parameter_name_wanted)
// {
//   int k=0;

//   while(k<=parameters_empty[j].size()-1)
//     {
//       if(parameter_name==parameter_name_wanted)
// 	{
// 	  parameter_value=parameters_empty[parameters_empty.size()-1];
// 	  found=true;
// 	  break;
// 	}
//       k++;
//     }
// }

// string get_last_value_loop2(vector<tuple<string, vector<string>>> empty_vec, string compartment_name_wanted, string parameter_name_wanted, string comp_name, string parameter_name)
// {
//   int j=0;
//   string parameter_name;
//   string parameter_value;
//   tuple<string, string> agh;
//   vector<string> parameters_empty;
//   string parameters_empty_j;

//   while(j<=empty_vec.size()-1)
//     {
//       // empty_vec_j=empty_vec[j];
//       parameter_name=get<0>(empty_vec[j]);
//       parameters_empty=get<1>(empty_vec[j]);

//       agh=split_string_in_two(parameter_name, parm_delim);
//       comp_name=get<0>(agh);
//       parameter_name=get<1>(agh);

//       if(compartment_name_wanted==comp_name)
// 	{
// 	  // parameters_empty_j=parameters_empty[j];
// 	  get_last_value_loop3(parameter_name, parameter_name_wanted);

// 	}
//       j++;
//     }
// }

// string get_last_value(string param)
// {
//   int i=0;
//   int j=0;
//   int k=0;
//   // string parameter_name;
//   // string parameter_value;
//   //  string comp_name;
//   //  vector<string> parameters_empty;
//   vector<tuple<string, vector<string>>> empty_vec;
//   bool found=false;
//   tuple<string, string> fg=split_string_in_two(param, parm_delim);
//   //  tuple<string, string> agh;
//   string compartment_name_wanted=get<0>(fg);
//   string parameter_name_wanted=get<1>(fg);
//   string comp_name;


//   tuple<
// 	     string, // compartment name
// 	     vector<
// 	            tuple<
// 	                  string, // parameter name
// 	                  vector<
// 	                  string // parameter values
// 	                 >
//       >     >      >
//        params_graph_i;



//   while(i<=params_graph.size()-1)
//     {
//       if(found)
// 	{
// 	  break;
// 	}

//       params_graph_i=params_graph[i];
//       comp_name=get<0>(params_graph_i);
//       empty_vec=get<1>(params_graph_i);
//       get_last_value_loop2(empty_vec, compartment_name_wanted, parameter_name_wanted, comp_name);

//       i++;
//     }

//   return parameter_value;
// }








string get_last_value(string param)
{
  int i=0;
  int j=0;
  int k=0;
  string parameter_name;
  string parameter_value;
  string comp_name;
  vector<string> parameters_empty;
  string parameters_empty_j;
  vector<tuple<string, vector<string>>> empty_vec;
  tuple<string, vector<string>> empty_vec_j;
  bool found=false;
  tuple<string, string> fg=split_string_in_two(param, parm_delim);
  tuple<string, string> agh;
  string compartment_name_wanted=get<0>(fg);
  string parameter_name_wanted=get<1>(fg);


  tuple<
	     string, // compartment name
	     vector<
	            tuple<
	                  string, // parameter name
	                  vector<
	                  string // parameter values
	                 >
      >     >      >
       params_graph_i;



  while(i<=params_graph.size()-1)
    {
      if(found)
	{
	  break;
	}

      params_graph_i=params_graph[i];
      comp_name=get<0>(params_graph_i);
      empty_vec=get<1>(params_graph_i);

      while(j<=empty_vec.size()-1)
	{
	  if(found)
	    {
	      break;
	    }

	  // empty_vec_j=empty_vec[j];
	  parameter_name=get<0>(empty_vec[j]);
	  parameters_empty=get<1>(empty_vec[j]);

	  agh=split_string_in_two(parameter_name, parm_delim);
	  comp_name=get<0>(agh);
	  parameter_name=get<1>(agh);

	  if(compartment_name_wanted==comp_name)
	    {
	      // cout<<"print"<<endl;
	      // print_vector(parameters_empty);
	      while(k<=parameters_empty.size()-1)
	      //	      while(k<=parameters_empty[j].size()-1)
		{
		  // cout<<"k "<<k<<"/"<<parameters_empty[j].size()-1<<endl;
		  // cout<<parameter_name<<", wanted "<<parameter_name_wanted<<endl;
		  if(parameter_name==parameter_name_wanted)
		    {
		      // cout<<parameter_name<<", wanted "<<parameter_name_wanted<<endl;
		      parameter_value=parameters_empty[parameters_empty.size()-1];
		      // cout<<parameter_value<<endl;

		      found=true;
		      break;
		    }
		  k++;
		}
	    }
	  k=0;
	  j++;
	}
      j=0;
      i++;
    }

  // cout<<" "<<endl;
  return parameter_value;
}

vector<string> get_multiple_last_values(vector<string> vec)
{
  int i=0;
  vector<string> rt;
  string str;
  string str1;

  while(i<=vec.size()-1)
    {
      str=vec[i];
      str1=get_last_value(str);
      rt.push_back(str1);
      i++;
    }

  return rt;
}

vector<string> replace_in_equation(vector<string> equation, int indice, string k_add)
{
  int i=indice;
  string replace;
  string k_add_1st;
  int equation_size=equation.size();
  string fchar;
  vector<string> equation_vec;

  k_add_1st=k_add[0];
  fchar=equation[i];

  if(k_add_1st==subtract)
    {
      replace=fchar+k_add;
    }
  else
    {
      replace=fchar+add+k_add;
    }

  equation_vec=equation_string_to_equation_vector(replace);
  replace=calculate_order_of_operations(equation_vec);

  equation=replace_in_vector(equation, replace, i, i);
  equation_size=equation.size();

  return equation;
}

string get_value_for_replace_whole_equation(string compartment_name_split, vector<string> params)
{
  int i=0;
  string global_compartment_names_i;
  int indice;
  string result;

  while(i<=global_compartment_names.size()-1)
    {
      global_compartment_names_i=global_compartment_names[i];

      if(compartment_name_split==global_compartment_names_i)
	{
	  indice=i;
	  break;
	}
      i++;
    }

  result=params[i];
  return result;
}

vector<string> replace_in_whole_equation(vector<string> equation, vector<int> indices, vector<string> params, string addition, vector<vector<string>> param_data)
{
  int i=0;
  tuple<string, string> param_splitted;
  tuple<string, string> string_splitted;
  string compartment_name_split;
  string value;
  string repl;
  vector<string> eq_params=param_data[asd];
  string eq_params_i;
  int indice;

  while(i<=indices.size()-1)
    {
      eq_params_i=eq_params[i];
      indice=indices[i];
      string_splitted=split_string_in_two(eq_params_i, parm_delim);
      compartment_name_split=get<0>(string_splitted);
      repl=get_value_for_replace_whole_equation(compartment_name_split, params);
      equation=replace_in_equation(equation, indice, repl);
      i++;
    }

  asd++;

  return equation;
}

// vector<int> indices_update2(vector<int> indices, int nr, int i_from)
// {
//   int i=i_from;

//   while(i<=indices.size()-1)
//     {
//       if(indices[i]!=1)
// 	{
// 	  indices[i]=indices[i]-nr;
// 	}
//       i++;
//     }
//   return indices;
// }


//int comp=0;

vector<string> values_to_add_update(vector<string> values_to_add, string constant)
{
  int i=0;
  double result;
  string result_str;
  const string zero="0";
  double constant_double;
  string values_to_add_i;
  double values_to_add_i_double;

  if(constant!=zero)
    {
      while(i<=values_to_add.size()-1)
	{
	  values_to_add_i=values_to_add[i];
	  values_to_add_i_double=stod(values_to_add_i);
	  constant_double=stod(constant);
	  result=constant_double*values_to_add_i_double;
	  result_str=to_string(result);
	  values_to_add[i]=result_str;
	  i++;
	}
    }

  return values_to_add;
}

// string order_of_operations(vector<string> equation, vector<int> math_op_ind)
// {
//   int i=0, i_from=0;
//   string math_operator, value1, value2, result;

//   // print_vector_int(math_op_ind);

//   while(i<=math_op_ind.size()-1)
//     {
//       if(equation.size()==1)
// 	{
// 	  break;
// 	}

//       // cout<<equation[math_op_ind[i]]<<endl;
//       //      print_vector_int(math_op_ind);
//       math_operator=equation[math_op_ind[i]];
//       value1=equation[math_op_ind[i]-1];
//       value2=equation[math_op_ind[i]+1];
//       result=get_math_operator(value1, value2, math_operator);
//       // cout<<value1<<math_operator<<value2<<"="<<result<<" "<<math_op_ind[i]-1<<" "<<math_op_ind[i]+1<<" "<<equation.size()-1<<endl;
//       equation=replace_in_vector(equation, result, math_op_ind[i]-1, math_op_ind[i]+1);
//       // print_vector(equation);
//       // cout<<" "<<endl;

//       // math_op_ind.erase(math_op_ind.begin()+1);

//       math_op_ind=indices_update2(math_op_ind, 2, i_from);

//       // if(equation.size()-1>1 and math_op_ind[i+1]!=1)
//       // 	{
//       // 	  // math_op_ind[i+1]=math_op_ind[i+1]-2
//       // 	  cout<<"math op ind "<<math_op_ind[i]<<" :"<<math_op_ind[i+1]<<": "<<math_op_ind.size()-1<<endl;
//       // 	  cout<<"math op ind update "<<math_op_ind[i]<<" :"<<math_op_ind[i+1]-2<<": "<<math_op_ind.size()-1<<endl;
//       // 	}

//       // math_op_ind[i+1]=math_op_ind[i+1]-2;

//       i++;
//     }

//   return equation[0];
// }

tuple<bool, int> is_in_vector(vector<string> vec, string str_find)
{
  // Checks if a string is in a string of vectors and return true/false and indice.
  int i=0;
  int is_in_indice=-1;
  bool rt=false;
  string fchar;
  tuple<bool, int> result;

  while(i<=vec.size()-1)
    {
      fchar=vec[i];

      if(str_find==fchar)
	{
	  rt=true;
	  is_in_indice=i;
	  break;
	}
      i++;
    }

  result=make_tuple(rt, is_in_indice);
  return result;
}
