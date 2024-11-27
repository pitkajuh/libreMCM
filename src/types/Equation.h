/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef EQUATION_H
#define EQUATION_H

#include "MathOperation.h"
#include <cstdint>

class EquationBase
{
private:
  uint8_t id;
public:
  double result=NAN;
  void SetId(const uint8_t id1){id=id1;}
  const uint8_t GetId(){return id;}
  // EquationBase(){}
  // EquationBase(const EquationBase &e)
  // {
  //   this->id=e.id;
  //   this->result=e.result;
  // }
  // EquationBase &operator=(EquationBase &e)
  // {
  //   std:: cout<<"EquationBase ="<<'\n';
  //   if(this==&e) return *this;

  //   this->id=e.id;
  //   this->result=e.result;

  //   return *this;
  // }
  virtual ~EquationBase(){};
};

class Equation: public EquationBase
{
public:
  Equation *next=nullptr;

  Equation(){}
  virtual ~Equation(){}
  virtual void SetValue(SMap &ValueMap)=0;
  virtual void Calculate()=0;
  virtual void GetType()=0;
  virtual void Print()=0;
};

class EquationSingle: public Equation
{
protected:
  MathOperationBase *m1=nullptr;
public:
  void SetValue(SMap &ValueMap)
  {
    cout<<this<<" Equation SetValue"<<'\n';
    m1->SetValue(ValueMap);
    if(!isnan(m1->result)) result=m1->result;
  }
  EquationSingle(){}
  EquationSingle(EquationSingle &e)
  {
    cout<<"EquationSingle copy"<<'\n';
    this->SetId(e.GetId());
    this->result=e.result;
    this->m1=e.GetMathOperation()->New(*e.GetMathOperation());
  }
  EquationSingle &operator=(EquationSingle &e)
  {
    std:: cout<<"EquationSingle ="<<'\n';
    if(this==&e) return *this;

    // this->id=e.id;
    // this->result=e.result;

    return *this;
  }
  void SetMathOperation(MathOperationBase *m){m1=m;}
  MathOperationBase *&GetMathOperation(){return m1;}
  void Calculate(){result=m1->result;}
  void Print()
  {
    cout<<"EquationSingle"<<'\n';
  }
  void GetType()
  {
    printf("new EquationSingle\n");
  }
  ~EquationSingle()
  {
    cout<<"Deleting "<<this<<" "<<std::to_string(GetId())<<" "<<m1<<'\n';
    delete m1;
  }
};

class EquationMulti: public Equation
{
protected:
  MathOperation *m1=nullptr;
public:
  void SetValue(SMap &ValueMap)
  {
    cout<<this<<" Equation SetValue"<<'\n';
    m1->SetValue(ValueMap);
    if(!isnan(m1->result)) result=m1->result;
  }
  EquationMulti(){}
  EquationMulti(EquationMulti &e)
  {
    cout<<"EquationMulti copy"<<'\n';
    this->SetId(e.GetId());
    this->result=e.result;
    this->m1=e.GetMathOperation()->New(*e.GetMathOperation());
  }
  void SetMathOperation(MathOperation *m)
  {
    cout<<"equation multi set math operation"<<'\n';
    m1=m;
  }
  MathOperation *&GetMathOperation(){return m1;}
  void Calculate(){result=m1->result;}
  void Print()
  {
    cout<<"EquationMulti"<<'\n';
  }
  void GetType()
  {
    printf("new EquationMulti\n");
  }
  ~EquationMulti()
  {
    cout<<"Deleting "<<this<<" "<<std::to_string(GetId())<<" "<<m1<<'\n';
    delete m1;
  }
};

class EquationMathOperator: public Equation
{
protected:
  MathOperator *math_operator=nullptr;
public:
  void SetOperator(const string &s)
  {
    if(s==ADD) math_operator=new Add;
    else if(s==SUBTRACT) math_operator=new Sub;
    else if(s==MULTIPLY) math_operator=new Mul;
    else if(s==DIVIDE) math_operator=new Div;
    else if(s==EXP) math_operator=new Exp;
  }
  EquationMathOperator(){}
  EquationMathOperator(EquationMathOperator &e)
  {
    cout<<"EquationMathOperator copy"<<'\n';
    this->SetId(e.GetId());
    this->result=e.result;
    // this->m1=e.GetMathOperation()->New(*e.GetMathOperation());
  }
  ~EquationMathOperator(){delete math_operator;}
};

class EquationValue: public EquationMathOperator
{
protected:
  Equation *m11=nullptr;
  Value *v=nullptr;
public:
  // void SetEquation(Equation *e){this->m11=e;}
  EquationValue(){}
  EquationValue(EquationValue &e)
  {
    cout<<"EquationValue copy"<<'\n';
    this->SetId(e.GetId());
    this->result=e.result;
    // this->v=e.GetValue()->New(*e.GetValue());
    // this->m1=e.GetMathOperation()->New(*e.GetMathOperation());
  }
  // Equation *GetNext()
  // {
  //   if(!isnan(m11->result) and !isnan(v->GetValue()))
  //     {
  // 	cout<<"result not nan "<<" previous "<<m11<<" "<<this<<'\n';
  // 	Calculate();
  // 	cout<<"result now "<<result<<'\n';
  // 	delete m11;
  // 	m11=nullptr;
  // 	delete v;
  // 	v=nullptr;
  // 	return this;
  // 	// m11->GetNext();
  //     }
  //   return m11->GetNext();
  // }
  // void Simplify()
  // {
  //   // cout<<this<<" "<<next<<" EquationValue simplify"<<" "<<result<<" "<<m11->result<<" "<<v->GetValue()<<" "<<m11->GetNext()<<'\n';
  //   m11->GetNext();
  //   // cout<<"NXT "<<m11->GetNext()<<'\n';
  //   Equation *nxt=m11->GetNext();
  //   // const double r=nxt->result;
  //   // cout<<"isnan(r) "<<" "<<r<<'\n';
  //   cout<<"nxt "<<nxt<<" "<<nxt->result<<'\n';
  //   if(!isnan(nxt->result))
  //     {
  // 	cout<<"!isnan(r) "<<nxt->result<<'\n';
  // 	// m11->result=next->result;

  // 	MathOperationBase *n=new MathOperation;
  // 	n->result=nxt->result;
  // 	delete m11;
  // 	m11=nullptr;
  // 	m11=new Equation;
  // 	m11->SetMathOperation(n);

  // 	// delete v;
  // 	// v=nullptr;
  //     }
  //   else
  //     {
  // 	cout<<"ELSE "<<'\n';
  //   // 	m11->GetNext();
  // 	nxt->Simplify();
  // 	// result=nxt->result;
  // 	Calculate();
  // 	cout<<nxt<<" "<<nxt->result<<" "<<result<<" "<<v->GetValue()<<'\n';
  //     }
  // }
  void SetValue(SMap &ValueMap)
  {
    cout<<"SetValue "<<"EquationValue"<<'\n';
    m11->SetValue(ValueMap);
  }
  Value *GetValue(){return v;}
  void Set(Equation *m0){this->m11=m0;}
  void SetValue(Value *w){v=w;}
  Equation *&Get(){return m11;}
  void Print()
  {
    cout<<"Equation"<<'\n';
  }
  void GetType()
  {
    printf("new EquationValue\n");
  }
  virtual ~EquationValue()
  {
    // cout<<m11<<" "<<m11->result<<" "<<v->GetName()<<" "<<v->GetValue()<<'\n';
    delete m11;
    delete v;
  }
};

class EquationV: public EquationValue
{
public:
  void Calculate(){result=math_operator->Calculate(GetValue()->GetValue(), Get()->result);}

  void SetValue(SMap &ValueMap)
  {
    cout<<"SetValue "<<"EquationV"<<'\n';
    m11->SetValue(ValueMap);
  }
  void Print()
  {
    cout<<"Equation"<<'\n';
  }
  void GetType()
  {
    printf("new EquationV\n");
  }
};

class EquationVNumerical: public EquationV
{
public:
  void SetValue(SMap &ValueMap)
  {
    cout<<"new EquationVNumerical SetValue "<<'\n';
    m11->SetValue(ValueMap);
  }
};

class EquationVConstant: public EquationV
{
public:
  void SetValue(SMap &ValueMap)
  {
    cout<<this<<" EquationVConstant SetValue "<<v->GetName()<<" "<<std::stod(ValueMap[v->GetName()])<<" "<<next<<'\n';
    v->SetValue(std::stod(ValueMap[v->GetName()]));
    m11->SetValue(ValueMap);
  }
  void GetType()
  {
    printf("new EquationVConstant\n");
  }
};

class EquationVVariable: public EquationV
{
public:
  void SetValue(SMap &ValueMap)
  {
    cout<<this<<" EquationVVariable SetValue "<<'\n';
    m11->SetValue(ValueMap);
  }
    void GetType()
  {
    printf("new EquationVVariable\n");
  }
};

class VEquation: public EquationValue
{
public:
  void Calculate(){result=math_operator->Calculate(GetValue()->GetValue(), Get()->result);}
  void SetValue(SMap &ValueMap)
  {
    cout<<"VEquation SetValue "<<'\n';
    m11->SetValue(ValueMap);
  }
  void Print()
  {
    cout<<"Equation"<<'\n';
  }
  void GetType()
  {
    printf("new VEquation\n");
  }
};

class VEquationNumerical: public VEquation
{
public:
  void SetValue(SMap &ValueMap)
  {
    cout<<"VEquationNumerical SetValue "<<'\n';
    m11->SetValue(ValueMap);
  }
};

class VEquationConstant: public VEquation
{
public:
  void SetValue(SMap &ValueMap)
  {
    cout<<this<<" VEquationConstant SetValue "<<v->GetName()<<" "<<std::stod(ValueMap[v->GetName()])<<" "<<next<<'\n';
    v->SetValue(std::stod(ValueMap[v->GetName()]));
    m11->SetValue(ValueMap);
  }
};

class VEquationVariable: public VEquation
{
public:
  void SetValue(SMap &ValueMap)
  {
    cout<<"VEquationVariable SetValue "<<'\n';
    m11->SetValue(ValueMap);
  }
};

class EquationMath: public EquationMathOperator
{
protected:
  Equation *m11=nullptr;
  Equation *m21=nullptr;
public:
  EquationMath(){}
  EquationMath(const EquationMath &e)
  {
    cout<<"EquationMath copy"<<'\n';
  }
  // void Simplify()
  // {
  //   cout<<this<<" EquationMathsimplify "<<result<<'\n';

  //   m11->Simplify();
  //   m21->Simplify();

  //   if(!isnan(m11->result) and !isnan(m21->result))
  //     {
  // 	cout<<"!isnan(m11->result) and !isnan(m21->result)"<<'\n';
  // 	Calculate();
  // 	cout<<this<<" result "<<result<<'\n';
  // 	cout<<m11<<" "<<m11->result<<" "<<m21<<" "<<m21->result<<'\n';
  // 	delete m11;
  // 	m11=nullptr;
  // 	delete m21;
  // 	m21=nullptr;
  // 	// Simplify();
  // 	// GetNext();
  //     }
  //   else
  //     {
  // 	cout<<"MATH ELSE"<<'\n';
  //     }
  // }
  void SetValue(SMap &ValueMap)
  {
    cout<<this<<" EquationMath SetValue"<<'\n';
    m11->SetValue(ValueMap);
    m21->SetValue(ValueMap);
  }
  Equation *&GetM1(){return m11;}
  Equation *&GetM2(){return m21;}
  void Set(Equation *m1, Equation *m2)
  {
    cout<<"Equation *m1, Equation *m2"<<'\n';
    m11=m1;
    m21=m2;
  }
  void Calculate(){result=math_operator->Calculate(m11->result, m21->result);}
  void Print()
  {
    cout<<"Equation"<<'\n';
  }
  void GetType()
  {
    printf("new EquationMath\n");
  }
  // EquationMath(){}
  virtual ~EquationMath()
  {
    delete m11;
    delete m21;
  }
};

#endif
