/*
  Created: 21.04.2022 21:00

  Author: pitkajuh
*/

/*
Reads a csv file "compartment.csv" containing a test compartments and transfer functions.
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
#include "read_compartment.h"

using namespace std;

int main()
{
  string csv_file="compartment.csv";
  vector<vector<string>> vec=read_csv(csv_file);

  int vec_ind=0;
  int vec_element=0;
  int nr=0;
  while(vec_ind<=vec.size()-1)
    {
      // cout<<vec[vec_ind].size()<<endl;
      cout<<"#########"<<endl;
      while(vec_element<=vec[vec_ind].size()-1)
	{
	  string value=vec[vec_ind][vec_element];
	  cout<<nr<<" "<<vec_ind<<" "<<value<<endl;
	  vec_element++;
	  nr++;
	}
      vec_ind++;
      vec_element=0;
    }
  // cout<<vec<<endl;
  return 0;
}
