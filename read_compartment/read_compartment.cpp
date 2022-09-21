/*
  Created: 19.04.2022 18:47

  Author: pitkajuh
*/

#include <iostream>
#include <stdlib.h>
#include <tuple>
#include <cmath>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

vector<string> line_read(string line)
{
  int i; // index
  string ab, empty_str=""; // empty strings used for appending
  int line_ln=line.length(); // length of the line from csv-file
  vector<string> empty; // empty vector for appending

  // iterates the line from csv-file character by character
  while(i<=line_ln)
    {

      if(line[i]==';')
	{
	  empty.push_back(ab);

	  // cout<<i<<" "<<ab<<endl;
	  ab="";
	}
      if(line[i]!=';')
	{
	  ab=ab+line[i];
	}
      if(i==line.length())
	{ // adds the last element, if it is the delimiter
	  if(line[line_ln-1]==';')
	    {
	      empty.push_back(empty_str);
	      // cout<<empty_str<<endl;
	    }
	  else
	    {

	      empty.push_back(ab);
	      // cout<<i<<" "<<ab<<endl;
	    }
	}
      i++;
    }
  int j=0;
  // cout<<empty[5]<<endl;
  // while(j<=5){
  //   cout<<j<<" "<<empty[j]<<endl;
  //   j++;
  // }
  // cout<<"############## "<<empty.size()<<endl;
  return empty;
  // cout<<"size "<<empty.size()<<endl;

}
// void read_csv(string csv_file){
vector<vector<string>> read_csv(string csv_file)
{
  // string csv_file="test.csv";
  fstream csv_loaded(csv_file, ios_base::in | ios::binary);
  string line, row;
  vector<string> diagonal;
  char lin;
  int test=0;
  vector<vector<string>> matrix;

  // append lines from csv-file to a matrix
  while(getline(csv_loaded, line))
    {
      // cout<<"test "<<test<<endl;
      matrix.push_back(line_read(line));
      // // if(test>=0){
      // //   cout<<line<<endl;
      // //   line_read(line);
      // // }
      // test++;
      // // break;
    }
  return matrix;
}
