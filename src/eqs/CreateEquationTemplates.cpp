/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "../types/MathOperation.h"
#include "../types/Data.h"
#include <iostream>
#include <cassert>

using std::cout;

void GetValue(const Data &data)
{
  // int j=0;
  // for(const auto &i: v)
  //   {
  //     // i->CalculateResult();
  //     i->Type();
  //     cout<<i->result<<'\n';
  //     // i->Simplify();
  //     // cout<<j<<" "<<i->GetV1Value()<<" "<<i->GetV2Value()<<" "<<i->result<<'\n';
  //     // cout<<j<<" "<<i->GetV1()<<" "<<i->GetV2()<<" "<<'\n';
  //     // cout<<j<<" "<<" "<<'\n';
  //     cout<<" "<<'\n';
  //     // delete i;
  //     j++;
  //   }
}

void Delete(Equation *head)
{
  Equation *current=head;
  Equation *prev=nullptr;
  Equation *next=nullptr;
  uint8_t i=0;

  while(current!=nullptr)
    {
      // cout<<to_str(head->GetId()<<'\n';
      assert(i==0);
      assert(current->next==nullptr);
      next=current->next;
      current->next=prev;
      prev=current;
      delete current;
      current=next;
      i++;
    }
}

void CreateEquationTemplates(const Data &data, const Map<string, Equation*> equationMap)
{
  cout<<"--------------------------------------"<<'\n';
  for(const auto &[name, equation]: equationMap)
    {
      // cout<<"name "<<name<<" "<<equation<<'\n';
      // equation->SetValue(data.constants_map);
      Delete(equation);
      // GetValue(equation, data);
    }
}
