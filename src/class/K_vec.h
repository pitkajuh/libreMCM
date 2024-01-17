/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef KVEC_H
#define KVEC_H

#include <string>
#include <vector>

using std::vector;
using std::string;
using std::to_string;

struct K_vec
{
  vector<double> t1;

  K_vec operator+(K_vec t)
  {
    const int size=t1.size();
    K_vec result;

    for(int i=0; i<=size; i++)
      {
	result.t1.push_back(t1[i]+t.t1[i]);
      }
    return result;
  }

  K_vec operator+(double t)
  {
    const int size=t1.size();
    K_vec result;

    for(int i=0; i<=size; i++)
      {
	result.t1.push_back(t1[i]+t);
      }
    return result;
  }

  K_vec operator*(K_vec t)
  {
    const int size=t1.size();
    K_vec result;

    for(int i=0; i<=size; i++)
      {
	result.t1.push_back(t1[i]*t.t1[i]);
      }
    return result;
  }

  K_vec operator*(double t)
  {
    const int size=t1.size();
    K_vec result;

    for(int i=0; i<=size; i++)
      {
	result.t1.push_back(t1[i]*t);
      }
    return result;
  }

  K_vec operator/(K_vec t)
  {
    const int size=t1.size();
    K_vec result;

    for(int i=0; i<=size; i++)
      {
	result.t1.push_back(t1[i]/t.t1[i]);
      }
    return result;
  }

  K_vec operator/(double t)
  {
    const int size=t1.size();
    K_vec result;

    for(int i=0; i<=size; i++)
      {
	result.t1.push_back(t1[i]/t);
      }
    return result;
  }

  const vector<string> to_str()
  {
    const int size=t1.size();
    vector<string> result;

    for(int i=0; i<=size; i++)
      {
	result.push_back(to_string(t1[i]));
      }
    return result;
  }
};

#endif
