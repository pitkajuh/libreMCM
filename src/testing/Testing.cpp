#include <cassert>
#include "../types/MathOperator.h"

int TestMathOperator()
{
  MathOperator *add=new Add;
  assert(add->Calculate(1, 1)==2);
  return 0;
}

int Testing()
{
  // int i=TestMathOperator();
  return 0;
}
