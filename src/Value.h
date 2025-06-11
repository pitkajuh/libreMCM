#ifndef VALUE_H
#define VALUE_H

class Value
{
private:
  double upperLimit;
  double value;
  double lowerLimit;
public:
  double currentValue;

  Value(){}
  virtual ~Value(){}
};

#endif
