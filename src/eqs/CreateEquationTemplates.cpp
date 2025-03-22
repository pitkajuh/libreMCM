/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "../types/Equation.h"
#include <iostream>
#include <cassert>

using std::cout;

void Delete(Equation *head)
{
  Equation *current=head;
  Equation *prev=nullptr;
  Equation *next=nullptr;

  while(current!=nullptr)
    {
      assert(current->next==nullptr);
      next=current->next;
      current->next=prev;
      prev=current;
      delete current;
      current=next;
      cout<<" "<<'\n';
    }
}

void Create(Equation *equation)
{
  cout<<"CEARTE"<<'\n';
  // equation->GetNext();
}

void CreateEquationTemplates(const Map<string, Equation*> equationMap, SMap &constantsMap)
{
  cout<<"--------------------------------------"<<'\n';
  Map<string, Equation*> differentialEquationMap;

  // for(const auto &[name, equation]: equationMap)
  //   {
  //     cout<<"name "<<name<<" "<<equation<<'\n';
  //     // equation->SetValue(constantsMap);
  //     cout<<" "<<'\n';
  //     // equation->Simplify();
  //     // Create(equation);
  //     cout<<" "<<'\n';
  //     delete equation;
  //     cout<<"---------------------------------------------------------"<<'\n';
  //     // Delete(equation);

  //     // GetValue(equation, data);
  //   }
}
