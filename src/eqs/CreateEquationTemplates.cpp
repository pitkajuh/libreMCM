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

void CreateEquationTemplates(const Map<string, Equation*> equationMap, SMap &constantsMap)
{
  cout<<"--------------------------------------"<<'\n';
  for(const auto &[name, equation]: equationMap)
    {
      cout<<"name "<<name<<" "<<equation<<'\n';
      equation->SetValue(constantsMap);
      cout<<" "<<'\n';
      Delete(equation);

      // GetValue(equation, data);
    }
}
