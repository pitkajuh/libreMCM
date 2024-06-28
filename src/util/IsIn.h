/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef ISIN_H
#define ISIN_H

bool IsIn(const string &s, const unordered_map<string, string> &f);
bool IsIn(const string &s, const vector<string> &f);

#endif
