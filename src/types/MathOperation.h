/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef MATHOPERATION_H
#define MATHOPERATION_H

#include <vector>
#include "Value.h"
#include "MathOperator.h"
#include "../global/mathconst.h"

class MathOperation;
using MathOperations=std::vector<MathOperation*>;
#include <iostream>
using std::cout;

class MathOperation
{
private:
  Value *v1;
  Value *v2;
  MathOperator *math_operator;
public:
  double result=NAN;
  MathOperation *prev=nullptr;

  // MathOperation(const MathOperation &m)
  // {
  //   cout<<"MathOperation copy"<<'\n';
  //   v1=m.v1;
  //   v2=m.v2;
  //   math_operator=m.math_operator;
  // }
  // MathOperation(MathOperation &&m)
  // {
  //   cout<<"MathOperation move"<<'\n';
  //   v1=m.v1;
  //   v2=m.v2;
  //   math_operator=m.math_operator;
  //   m.v1=nullptr;
  //   m.v2=nullptr;
  //   m.math_operator=nullptr;
  // }
  // MathOperation& operator=(MathOperation &&m)
  // {
  //   if(this!=&m)
  //     {
  // 	delete v1;
  // 	delete v2;
  // 	delete math_operator;
  // 	v1=m.v1;
  // 	v2=m.v2;
  // 	math_operator=m.math_operator;
  // 	m.v1=nullptr;
  // 	m.v2=nullptr;
  // 	m.math_operator=nullptr;
  //     }
  //   return *this;
  // }
  void SetOperator(const string &m)
  {
    if(m==ADD) math_operator=new Add;
    else if(m==SUBTRACT) math_operator=new Sub;
    else if(m==MULTIPLY) math_operator=new Mul;
    else if(m==DIVIDE) math_operator=new Div;
    else if(m==EXP) math_operator=new Exp;
  }
  void Set(Value *v, const string &m, Value *w)
  {
    v1=v;
    v2=w;
    SetOperator(m);
  }
  MathOperation()=default;
  MathOperator *GetOp(){return math_operator;} const
  void SetOp(MathOperator *m){math_operator=m;}
  Value *GetV1(){return v1;}
  Value *GetV2(){return v2;} const
  double GetV1Value(){return v1->GetValue();} const
  double GetV2Value(){return v2->GetValue();} const
  string GetV1Name(){return v1->GetName();} const
  string GetV2Name(){return v2->GetName();} const
  void SetV1Value(const double &d){v1->SetValue(d);} const
  void SetV2Value(const double &d){v2->SetValue(d);} const
  void SetV1Name(const string&s){v1->SetName(s);} const
  void SetV2Name(const string&s){v2->SetName(s);} const
  void SetV1(Value *v){v1=v;}
  void SetV2(Value *v){v2=v;}
  void CalculateResult(){result=GetOp()->Calculate1(GetV1Value(), GetV2Value());}
  virtual MathOperation *New()=0;
  virtual void Link(MathOperations &op, const unsigned int &i, const unsigned int &j)=0;
  virtual void Type()=0;
  virtual void Calculate()=0;
  virtual ~MathOperation()
  {
    cout<<"clean v1 "<<v1<<'\n';
    delete v1;
    cout<<"clean v2 "<<v2<<'\n';
    delete v2;
    cout<<"mo "<<math_operator<<'\n';
    delete math_operator;
    cout<<"mo deleted"<<'\n';
    delete prev;

    cout<<" "<<'\n';
  }
};

class MMMathOperation: public MathOperation
{
   // Math-math math operation
public:
  MathOperation *New()
  {
    MathOperation *n=new MMMathOperation;
    return n;
  }
  void Link(MathOperations &op, const unsigned int &i, const unsigned int &j)
  {
    // prev=std::move(op[i]);
    prev=op[i]->New();
    prev->SetV1(op[i]->GetV1()->New());
    prev->SetV1Value(op[i]->GetV1Value());
    prev->SetV1Name(op[i]->GetV1Name());
    prev->SetV2(op[i]->GetV2()->New());
    prev->SetV2Value(op[i]->GetV2Value());
    prev->SetV2Name(op[i]->GetV2Name());
    prev->SetOp(op[i]->GetOp()->New());
    cout<<"prev v1 "<<prev->GetV1()<<" v2 "<<prev->GetV2()<<" mo "<<prev->GetOp()<<'\n';
    // cout<<"prev v1 "<<prev->GetV1Value()<<" v2 "<<prev->GetV2()<<" mo "<<prev->GetOp()<<'\n';

    SetV1(op[j]->GetV1()->New());
    SetV1Value(op[j]->GetV1Value());
    SetV1Name(op[j]->GetV1Name());
    SetV2(op[j]->GetV2()->New());
    SetV2Value(op[j]->GetV2Value());
    SetV2Name(op[j]->GetV2Name());
    SetOp(op[j]->GetOp()->New());
    cout<<"v1 "<<GetV1()<<" v2 "<<GetV2()<<" mo "<<GetOp()<<'\n';
    // cout<<"v1 "<<GetV1()<<" v2 "<<GetV2()<<" mo "<<GetOp()<<'\n';

    // delete op[j];

    // op[i]=nullptr;

    // if(prev->result!=NAN)
    //   {

    // op[i]=nullptr;
    // op[j]=nullptr;
    // if(op.size()>1)
    //   {
    // 	cout<<"op.size()>1"<<'\n';
    // 	delete op[i];
    // 	op.erase(op.begin()+i);
    //   }
    //   if(op.size()>1)
    // 	{
    // 	  cout<<"2op.size()>1"<<'\n';
    // 	  delete op[j];
    // 	  op.erase(op.begin()+j);
    // 	}
  }
  void Calculate()
  {
    CalculateResult();
    cout<<"result calculated "<<result<<'\n';
  }
  void Type(){cout<<"Type is MMMath"<<'\n';}
};

class NMMathOperation: public MathOperation
{
  // Numeric-math math operation
public:
  // MathOperation *prev=nullptr;
  MathOperation *New()
  {
    MathOperation *n=new NMMathOperation;
    return n;
  }
  void Link(MathOperations &op, const unsigned int &i, const unsigned int &j)
  {
    prev=std::move(op[i]);

    // if(prev->result!=NAN)
    //   {
    // 	op.erase(op.begin()+i);
    //   }
  }

  void Type(){cout<<"Type is NMMath"<<'\n';}
  void Calculate()
  {
    CalculateResult();
    cout<<"result calculated "<<result<<'\n';
  }
};

class MVMathOperation: public MathOperation
{
  // Math-variable math operation
public:
  MathOperation *New()
  {
    MathOperation *n=new MVMathOperation;
    return n;
  }
  void Link(MathOperations &op, const unsigned int &i, const unsigned int &j)
  {
    prev=std::move(op[i]);

    // if(prev->result!=NAN)
    //   {
    // 	op.erase(op.begin()+i);
    //   }
  }
  void Calculate(){}
  void Type(){cout<<"Type is MVMath"<<'\n';}
};

class CMMathOperation: public MathOperation
{
  // Constant-math math operation
public:
  MathOperation *New()
  {
    MathOperation *n=new CMMathOperation;
    return n;
  }
  void Link(MathOperations &op, const unsigned int &i, const unsigned int &j)
  {
    prev=std::move(op[i]);

    // if(prev->result!=NAN)
    //   {
    // 	op.erase(op.begin()+i);
    //   }
  }
  void Calculate(){}
  void Type(){cout<<"Type is CMMath"<<'\n';}
};

class NNMathOperation: public MathOperation
{
  // Numeric-numeric math operation
public:
  MathOperation *New()
  {
    MathOperation *n=new NNMathOperation;
    return n;
  }
  void Calculate(){CalculateResult();}
  void Type(){cout<<"Type is NNMath"<<'\n';}
  void Link(MathOperations &op, const unsigned int &i, const unsigned int &j){}
};

class VVMathOperation: public MathOperation
{
  // Variable-variable math operation
public:
  MathOperation *New()
  {
    MathOperation *n=new VVMathOperation;
    return n;
  }
  void Calculate(){}
  void Type(){cout<<"Type is VVMath"<<'\n';}
  void Link(MathOperations &op, const unsigned int &i, const unsigned int &j){}
};

class CVMathOperation: public MathOperation
{
  // Constant-variable math operation
public:
  MathOperation *New()
  {
    MathOperation *n=new CVMathOperation;
    return n;
  }
  void Calculate(){}
  void Type(){cout<<"Type is CVMath"<<'\n';}
  void Link(MathOperations &op, const unsigned int &i, const unsigned int &j){}
};

class CCMathOperation: public MathOperation
{
  // Constant-constant math operation
public:
  MathOperation *New()
  {
    MathOperation *n=new CCMathOperation;
    return n;
  }
  void Calculate(){}
  void Type(){cout<<"Type is CCMath"<<'\n';}
  void Link(MathOperations &op, const unsigned int &i, const unsigned int &j){}
};

class NVMathOperation: public MathOperation
{
  // Numeric-variable math operation
public:
  MathOperation *New()
  {
    MathOperation *n=new NVMathOperation;
    return n;
  }
  void Calculate(){}
  void Type(){cout<<"Type is NVMath"<<'\n';}
  void Link(MathOperations &op, const unsigned int &i, const unsigned int &j){}
};

class NCMathOperation: public MathOperation
{
  // Numeric-constant math operation
public:
  MathOperation *New()
  {
    MathOperation *n=new NCMathOperation;
    return n;
  }
  void Calculate(){}
  void Type(){cout<<"Type is NCMath"<<'\n';}
  void Link(MathOperations &op, const unsigned int &i, const unsigned int &j){}
};

#endif
