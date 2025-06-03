#ifndef PARSEQUATIONS_H
#define PARSEQUATIONS_H

#include "GraphEquation.h"

map<string, GraphEquation*> ParseEquations(const map<string, vector<string>> &equations_map, const vector<string> &data);

#endif
