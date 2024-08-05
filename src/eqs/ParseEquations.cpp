/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "CreateNewMathOperation.h"
#include "ToVector.h"
#include "test.h"
#include "../global/mathconst.h"
#include "../types/MathOperation.h"
#include "../types/Data.h"
#include "../util/IsIn.h"
#include <algorithm>
#include <iostream>
#include <cmath>

using std::to_string;
using std::cout;
using std::stod;
using std::stoi;

void print_vector2(vector<string> vec)
{
  int i=0;
  string empty="";

  while(i<=vec.size()-1 && vec.size()>0)
    {
      if(i==0)  empty=vec[i];
      else empty=empty+";"+vec[i];
      i++;
    }
  cout<<empty<<'\n';
}

void print(MathOperation *m)
{
  MathOperation *c=m;
    cout<<"print start"<<'\n';
  while(c!=nullptr)
    {
      cout<<c<<" "<<c->GetV1()<<" "<<c->GetOp()<<" "<<c->GetV2()<<'\n';
      c=c->next;
    }
  cout<<"print end"<<'\n';
}

MathOperation *Search(MathOperation *m, const unsigned int i)
{
  MathOperation *c=m;

  while(c!=nullptr)
    {
      if(c->id==i){return c;}
      c=c->next;
    }
  return nullptr;
}

MathOperation *NewOperation(MathOperation *m)
{
  MathOperation *mo1=m->New();
  mo1->SetV1(m->GetV1()->New());
  mo1->SetV1Value(m->GetV1Value());
  mo1->SetV1Name(m->GetV1Name());
  mo1->SetV2(m->GetV2()->New());
  mo1->SetV2Value(m->GetV2Value());
  mo1->SetV2Name(m->GetV2Name());
  mo1->SetOp(m->GetOp()->New());
  mo1->id=m->id;
  return mo1;
}

MathOperation *Delete(MathOperation *head, const unsigned int i)
{
  cout<<"Deleteing id "<<i<<" "<<head<<'\n';
  MathOperation *temp=head;
  MathOperation *prev;

  // if(temp!=nullptr){return head;}

  if(temp->id==i)
    {
      cout<<"temp->id==id"<<'\n';
      head=temp->next;
      // if(head->next->id==i)
      // if(temp->next->id==i)
      // 	{
      // 	  // head->next=nullptr;
      // 	  temp->next=nullptr;
      // 	  cout<<"head->next.id==i"<<'\n';
      // 	}
      // prev->next=temp->next;
      delete temp;
      // temp=nullptr;
      return head;
    }



  while(temp->id!=i)
  // while(temp!=nullptr)
    {
      cout<<"finding id "<<temp->id<<'\n';
      // if(temp->id==i)
      // 	{
      // 	  cout<<"break"<<'\n';
      // 	  break;
      // 	}
      prev=temp;
      temp=temp->next;
    }
  cout<<"loop ok"<<'\n';
  if(temp!=nullptr)
    {
      prev->next=temp->next;
      // head = head->next;
      delete temp;
    }
  else
    {
      cout<<"Net deleteing"<<'\n';
      // prev->next = prev->next->next;
      // return head;
    }
  cout<<"Delete end"<<'\n';
  return head;
}

MathOperation *NewNMMath(const string &s1, const string &s2, const string &o, const unsigned int &k, MathOperations &ooo, MathOperation *&c)
{
  Value *v1=new Numeric;
  v1->SetValue(stod(s1));
  MathOperation *m=new NMMathOperation;
  m->id=k;
  m->SetV1(v1);
  MathOperation *m1=Search(c, stoi(s2.substr(1, s2.size())));
  Value *v2=m1->GetV2()->New();
  v2->SetName(m1->GetV2()->GetName());
  v2->SetValue(m1->GetV2()->GetValue());
  m->Set(v1, o, v2);
  const double result=m1->result;

  if(result!=NAN)
    {
      m->SetV2Value(result);
      m->Calculate();
    }
  else
    {
      cout<<"else NewNMMath"<<'\n';
    }
  return m;
}

MathOperation *NewMVMath(const string &s1, const string &s2, const string &o, const unsigned int &k, MathOperations &ooo, MathOperation *&c)
{
  Value *v2=new Variable;
  v2->SetName(s2);
  MathOperation *m=new MVMathOperation;
  m->id=k;
  m->SetV2(v2);
  // const double result=ooo[stoi(s1.substr(1, s1.size()))]->result;
  const double result=Search(c, stoi(s1.substr(1, s1.size())))->result;

  if(result!=NAN)
    {
      Value *v1=new Numeric;
      v1->SetValue(result);
      m->Set(v1, o, v2);
    }
  else
    {
      cout<<"else NewNVMath"<<'\n';
    }
  return m;
}

MathOperation *NewCMMath(const string &s1, const string &s2, const string &o, const unsigned int &k, MathOperations &ooo, MathOperation *&c)
{
  Value *v1=new Constant;
  v1->SetName(s1);
  MathOperation *m=new CMMathOperation;
  m->id=k;
  m->SetV1(v1);
  const double result=Search(c, stoi(s2.substr(1, s2.size())))->result;

  if(result!=NAN)
    {
      Value *v2=new Numeric;
      v2->SetValue(result);
      m->Set(v1, o, v2);
    }
  else
    {
      cout<<"else NewCVMath"<<'\n';
    }
  return m;
}

MathOperation *Val2(MathOperation *&c, const vector<string> &equation, const unsigned int i, const Data &data, MathOperations &ooo, const unsigned int &k, MathOperation *&next)
{
  const string s1=equation[i-1];
  const string s2=equation[i+1];
  const string o=equation[i];
  const bool s1_variable=IsIn(s1, data.diagonal);
  const bool s1_constant=IsIn(s1, data.constants_map);
  const bool s1_numeric=IsNumerical(s1);
  const bool s1_math=(s1.substr(0, 1)=="@") ? true : false;
  const bool s2_variable=IsIn(s2, data.diagonal);
  const bool s2_constant=IsIn(s2, data.constants_map);
  const bool s2_numeric=IsNumerical(s2);
  const bool s2_math=(s2.substr(0, 1)=="@") ? true : false;
  // cout<<"Math operation "<<ooo.size()<<'\n';
  // cout<<"   "<<"v"<<" "<<"c"<<" "<<"n"<<" "<<"m"<<'\n';
  // cout<<"s1 "<<s1_variable<<" "<<s1_constant<<" "<<s1_numeric<<" "<<s1_math<<'\n';
  // cout<<"s2 "<<s2_variable<<" "<<s2_constant<<" "<<s2_numeric<<" "<<s2_math<<'\n';

  if(s1_variable and s2_variable){return CreateNewMathOperation2<Variable, Variable, VVMathOperation>(s1, s2, o, k);}
  else if(s1_variable and s2_constant){return CreateNewMathOperation2<Constant, Variable, CVMathOperation>(s2, s1, o, k);}
  else if(s1_variable and s2_numeric){return CreateNewMathOperation<Numeric, Variable, NVMathOperation>(s2, s1, o, k);}
  else if(s1_constant and s2_variable){return CreateNewMathOperation2<Constant, Variable, CVMathOperation>(s1, s2, o, k);}
  else if(s1_constant and s2_constant){return CreateNewMathOperation2<Constant, Constant, CCMathOperation>(s1, s2, o, k);}
  else if(s1_constant and s2_numeric){return CreateNewMathOperation<Numeric, Constant, NCMathOperation>(s2, s1, o, k);}
  else if(s1_numeric and s2_variable){return CreateNewMathOperation<Numeric, Variable, NVMathOperation>(s1, s2, o, k);}
  else if(s1_numeric and s2_constant){return CreateNewMathOperation<Numeric, Constant, NCMathOperation>(s1, s2, o, k);}
  else if(s1_variable and s2_math){return NewMVMath(s2, s1, o, k, ooo, c);}
  else if(s1_constant and s2_math){return NewCMMath(s1, s2, o, k, ooo, c);}
  else if(s1_numeric and s2_math){return NewNMMath(s1, s2, o, k, ooo, c);}
  else if(s1_math and s2_variable){return NewMVMath(s1, s2, o, k, ooo, c);}
  else if(s1_math and s2_constant){return NewCMMath(s2, s1, o, k, ooo, c);}
  else if(s1_math and s2_numeric){return NewNMMath(s2, s1, o, k, ooo, c);}
  else if(s1_numeric and s2_numeric)
    {
      Value *v1=new Numeric;
      v1->SetValue(stod(s1));
      Value *v2=new Numeric;
      v2->SetValue(stod(s2));
      MathOperation *m=new NNMathOperation;
      m->id=k;
      m->SetV1(v1);
      m->SetV2(v2);
      m->SetOperator(o);
      m->Calculate();
      return m;
    }
  else if(s1_math and s2_math)
    {
      cout<<"s1_math and s2_math"<<'\n';
      MMMathOperation *m=new MMMathOperation;
      m->id=k;
      // m->next=nullptr;
      MathOperation *m1=Search(c, stoi(s1.substr(1, s1.size())));
      MathOperation *m2=Search(c, stoi(s2.substr(1, s2.size())));
      const double result1=m1->result;
      const double result2=m2->result;
      // cout<<result1<<" "<<result2<<'\n';
      // cout<<m1<<" "<<m2<<'\n';
      // cout<<m1->GetV1Value()<<" "<<m1->GetV2Value()<<" "<<m2->GetV1Value()<<" "<<m2->GetV2Value()<<'\n';
      if(!isnan(result1) and !isnan(result2))
	{
	  // cout<<"!isnan(result1) and !isnan(result2)"<<'\n';
	  Value *v1=new Numeric;
	  v1->SetValue(result1);
	  Value *v2=new Numeric;
	  v2->SetValue(result2);
	  m->Set(v1, o, v2);
	  m->Calculate();
	}
      else
	{
	  MathOperation *mo1=NewOperation(m1);
	  MathOperation *mo2=NewOperation(m2);

	  m->mo1=mo1;
	  m->mo2=mo2;
	  m->SetOperator(o);

	  cout<<mo1<<" v1 "<<mo1->GetV1()<<" v2 "<<mo1->GetV2()<<" mo "<<mo1->GetOp()<<" "<<mo1->id<<'\n';
	  cout<<mo2<<" v1 "<<mo2->GetV1()<<" v2 "<<mo2->GetV2()<<" mo "<<mo2->GetOp()<<" "<<mo2->id<<'\n';
	  cout<<"linked "<<'\n';
	  cout<<" "<<'\n';

	  // m->Link(m1, m2, o);
	  // print(m);
	  // m=Delete(m1, m1_id);
	  m2=Delete(m2, m1->id);
	  m2=Delete(m2, m2->id);
	  // delete m1;
	  // delete m2;

	  // m2=Delete(m2, m1->id);
	  // m2=Delete(m2, m2->id);
	}
      return m;
    }
  else if(!s1_variable && !s1_constant && !s1_numeric && !s1_math)
    {
      throw std::invalid_argument("Value \""+s1+"\" is not a constant, variable/compartment or numeric value.");
    }
  else
    {
      throw std::invalid_argument("Value \""+s2+"\" is not a constant, variable/compartment or numeric value.");
    }
}

vector<string> FindOperator(vector<string> equation, const string &find, unsigned int &k, MathOperations &ooo, const Data &data, MathOperation *&e, MathOperation *&next)
{
  unsigned int i=0;
  MathOperation *m;

  while(i<equation.size())
    {
      // cout<<i<<"/"<<equation.size()<<" "<<next<<'\n';
      if(find==equation[i])
	{
	  // m=Val(equation, i, data, ooo, k);

	  e=Val2(e, equation, i, data, ooo, k, next);
	  // e->Print();
	  // cout<<e<<" v1 "<<e->GetV1()<<" "<<e->GetOp()<<" v2 "<<e->GetV2()<<'\n';
	  cout<<"next "<<next<<'\n';
	  e->next=next;
	  next=e;


	  // ooo.emplace_back(m);
	  cout<<"Adding "<<"@"+to_string(k)<<"="<<equation[i-1]<<equation[i]<<equation[i+1]<<" "<<ooo.size()<<'\n';
	  equation[i]="@"+to_string(k);
	  equation.erase(equation.begin()+i+1);
	  equation.erase(equation.begin()+i-1);
	  // cout<<"k="<<k<<" size "<<ooo.size()<<'\n';
	  k++;

	  i=0;
	  cout<<" "<<'\n';
	  continue;
	}
      i++;
    }
  return equation;
}

void GetOrder(vector<string> &equation, unsigned int &k, MathOperations &ooo, const Data &data, MathOperation *&e, MathOperation *&next)
{
  for(const auto&i: OPERATORS) equation=FindOperator(equation, i, k, ooo, data, e, next);
}

vector<string> RemoveOpenClose(vector<string> equation)
{
  // Removes unnecessary parenthesis from equations such as ((1+(a+b)))
  const unsigned int open=distance(equation.begin(), find(equation.begin(), equation.end(), OPEN));
  const unsigned int close=distance(equation.begin(), find(equation.begin(), equation.end(), CLOSE));
  if(open!=equation.size() and close!=equation.size()) equation=Remove(equation, open, close);
  return equation;
}

vector<string> GetParenthesis(const vector<string> &equation, const int &open, const int &close, unsigned int &k, MathOperations &ooo, const Data &data, MathOperation *&e, MathOperation *&next)
{
  vector<string> v1{equation.begin()+open+1, equation.begin()+close};
  GetOrder(v1, k, ooo, data, e, next);
  v1=test(v1, k, ooo, data, e, next);
  const vector<string> v2{equation.begin(), equation.begin()+open};
  const vector<string> v3{equation.begin()+close+1, equation.end()};
  vector<string> result;
  result.reserve(v1.size()+v2.size()+v3.size());
  result.insert(result.begin(), v2.begin(), v2.end());
  result.insert(result.end(), v1.begin(), v1.end());
  result.insert(result.end(), v3.begin(), v3.end());
  print_vector2(result);
  return result;
}

Map<string, MathOperations> ParseEquations(const SMap &equations_map, const Data &data)
{
    // Set calculation order of an equation according to order of operations:

    // 1. Parentheses
    // 2. Exponents
    // 3. Multiplication and division
    // 4. Addition and subtraction

  vector<string> v;
  unsigned int k=0;
  MathOperations ooo;
  MathOperation *e=nullptr;
  MathOperation *next=nullptr;
  Map<string, MathOperations> equations_map2;
  equations_map2.reserve(equations_map.size());

  for(const auto& [name, equation]: equations_map)
    {
      v=ToVector(equation);
      v=RemoveOpenClose(v);
      cout<<"EQUATION"<<'\n';
      print_vector2(v);
        cout<<" "<<'\n';
      v=test(v, k, ooo, data, e, next);
      GetOrder(v, k, ooo, data, e, next);
      // equations_map2[name]=ooo;
      // cout<<"size "<<ooo.size()<<'\n';

      // cout<<e<<" v1 "<<e->GetV1()<<" mo "<<e->GetOp()<<" v2 "<<e->GetV2()<<'\n';

      // cout<<e<<'\n';
      // cout<<"v1 "<<e->GetV1()<<'\n';
      // cout<<"mo "<<e->GetOp()<<'\n';
      // cout<<"v2 "<<e->GetV2()<<'\n';

      // cout<<next<<" v1 "<<next->GetV1()<<" mo "<<next->GetOp()<<" v2 "<<next->GetV2()<<'\n';

      // delete e;
      // delete next;
      k=0;
      ooo.clear();
      cout<<" "<<'\n';
    }
  // delete e;
  // MathOperation *tmp=e;
  // while(tmp!=nullptr)
  //   {
  //     tmp=tmp->next;
  //     delete e;
  //     e=tmp;
  //     cout<<" "<<'\n';
  //   }
  return equations_map2;
}
