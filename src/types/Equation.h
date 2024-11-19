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
#include "MathOperator.h"
#include <cstdint>

class Equation;

class EquationBase
{
private:
  uint8_t id;
public:
  double result=NAN;
  void SetId(const uint8_t id1){id=id1;}
  const uint8_t GetId(){return id;}
  virtual Equation *GetNext()=0;
  virtual void Simplify()=0;
  virtual void SetValue(SMap &ValueMap)=0;
  virtual void Calculate()=0;
  virtual void GetType()=0;
  virtual void Print()=0;
  virtual ~EquationBase(){};
};

class Equation: public EquationBase
{
protected:
  MathOperationBase *m1=nullptr;
public:
  Equation *next=nullptr;

  Equation *GetNext()
  {
    return this;
  }
  void SetValue(SMap &ValueMap)
  {
    cout<<this<<" Equation SetValue"<<'\n';
    m1->SetValue(ValueMap);
    if(!isnan(m1->result)) result=m1->result;
  }
  void SetMathOperation(MathOperationBase *m){m1=m;}
  MathOperationBase *&GetMathOperation(){return m1;}
  void Calculate(){result=m1->result;}
  void Simplify()
  {
    cout<<this<<" "<<m1<<" "<<result<<" Equation simplify"<<'\n';

    if(!isnan(result))
      {
	cout<<"Equation EquationBase !isnan(result)"<<'\n';
	delete m1;
	m1=nullptr;
      }

  }
  void Print()
  {
    cout<<"Equation"<<'\n';
  }
  void GetType()
  {
    printf("new normal Equation\n");
  }
  ~Equation()
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
  ~EquationMathOperator(){delete math_operator;}
};

class EquationValue: public EquationMathOperator
{
protected:
  Equation *m11=nullptr;
  Value *v=nullptr;
public:
  Equation *GetNext()
  {
    if(!isnan(m11->result) and !isnan(v->GetValue()))
      {
	cout<<"result not nan "<<" previous "<<m11<<" "<<this<<'\n';
	Calculate();
	cout<<"result now "<<result<<'\n';
	delete m11;
	m11=nullptr;
	delete v;
	v=nullptr;
	return this;
	// m11->GetNext();
      }
    return m11->GetNext();
  }
  void Simplify()
  {
    // cout<<this<<" "<<next<<" EquationValue simplify"<<" "<<result<<" "<<m11->result<<" "<<v->GetValue()<<" "<<m11->GetNext()<<'\n';
    m11->GetNext();
    // cout<<"NXT "<<m11->GetNext()<<'\n';
    Equation *nxt=m11->GetNext();
    // const double r=nxt->result;
    // cout<<"isnan(r) "<<" "<<r<<'\n';
    cout<<"nxt "<<nxt<<" "<<nxt->result<<'\n';
    if(!isnan(nxt->result))
      {
	cout<<"!isnan(r) "<<nxt->result<<'\n';
	// m11->result=next->result;

	MathOperationBase *n=new MathOperation;
	n->result=nxt->result;
	delete m11;
	m11=nullptr;
	m11=new Equation;
	m11->SetMathOperation(n);

	// delete v;
	// v=nullptr;
      }
    else
      {
	cout<<"ELSE "<<'\n';
    // 	m11->GetNext();
	nxt->Simplify();
	// result=nxt->result;
	Calculate();
	cout<<nxt<<" "<<nxt->result<<" "<<result<<" "<<v->GetValue()<<'\n';
      }
  }
  void SetValue(SMap &ValueMap)
  {
    cout<<"SetValue "<<"EquationValue"<<'\n';
    m11->SetValue(ValueMap);
  }
  Value *GetValue(){return v;}
  void Set(Equation *m0){m11=m0;}
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
    // cout<<m11<<" "<<m11->result<<" "<<'\n';
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
  void Simplify()
  {
    cout<<this<<" EquationMathsimplify "<<result<<'\n';

    m11->Simplify();
    m21->Simplify();

    if(!isnan(m11->result) and !isnan(m21->result))
      {
	cout<<"!isnan(m11->result) and !isnan(m21->result)"<<'\n';
	Calculate();
	cout<<this<<" result "<<result<<'\n';
	cout<<m11<<" "<<m11->result<<" "<<m21<<" "<<m21->result<<'\n';
	delete m11;
	m11=nullptr;
	delete m21;
	m21=nullptr;
	// Simplify();
	// GetNext();
      }
    else
      {
	cout<<"MATH ELSE"<<'\n';
      }
  }
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
  virtual ~EquationMath()
  {
    delete m11;
    delete m21;
  }
};

#endif
