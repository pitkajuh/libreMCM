#ifndef FILEEQUATIONS_H
#define FILEEQUATIONS_H

#include <unordered_set>
#include "Bools.h"
#include "FileGraph.h"
#include "Equation.h"

struct TestStr
{
public:
  string str1;
  string op;
  string str2;
};

struct MathOperators
{
public:
  MathOperator *add=new Add;
  MathOperator *subtract=new Sub;
  MathOperator *multiply=new Mul;
  MathOperator *divide=new Div;
  MathOperator *power=new Exp;

  MathOperator *GetOperator(const string &o)
  {
    if(o=="+") return add;
    else if(o=="-") return subtract;
    else if(o=="*") return multiply;
    else if(o=="/") return divide;
    else return power;
  }

  MathOperators(){}
  ~MathOperators()
  {
    delete add;
    delete subtract;
    delete multiply;
    delete divide;
    delete power;
  }
};

enum class Types{variable, constant, numeric, math, NotFound};

class FileEquations: public File
{
protected:
  Types GetTypes(const Bools &b);
  void CreateVertex(const string &s1, const string &s2, const string &mathOperator, const Bools &b1, const Bools &b2, MathOperators &operators, vector<VertexNew> &vv, double *variableValue, const vector<uint16_t> &noOfInitialValue, map<string, uint16_t> &data, vector<uint8_t> &removeIndices, std::unordered_set<double*> removeAddress);
  void GetOrder(string &str, uint8_t &id, vector<TestStr> &a);
  void RemoveOpenClose(string &equation, uint8_t &id, vector<TestStr> &a);
  void Convert(const map<uint16_t, string> &map);
  uint8_t GetOpen(const string &str, const uint8_t close);
  uint8_t GetLeft(string &str);
  uint8_t GetRight(const string &eq);
  streampos SA(ifstream &file, streampos from, const string &line);
  vector<TestStr> ToVector(string &eq);
public:
  map<uint16_t, double> constants;
  map<uint16_t, string> equations;
  map<string, uint16_t> equationNames;
  map<string, uint16_t> constantNames;

  Equations ParseEquations(map<string, uint16_t> &data, MathOperators &operators, double *variableValue, const vector<uint16_t> &noOfInitialValue);

  FileEquations(const string &fileName);
  FileEquations(){}
  ~FileEquations(){}
};

#endif
