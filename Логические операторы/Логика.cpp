// les10.cpp: определяет точку входа для приложения.
//

#include "logic_elemets.h"
#include "std_lib_facilities.h"

namespace Logic {
void Element::calculate()
{
  switch (type)
  {
  case Type::Sourse:
    break;
  case Type::OperationAND:
  {
    bool flag = true;
    set(true);
    for (auto input : inputs)
    {
      if (!*input)
      {
          flag=false;
          break;
      }
    }
    set(flag);
    break;
  }
  case Type::OperationOR:
  {
    bool flag=false;
    for (auto input : inputs)
    {
      if (*input)
      {
          flag = true;
          break;
      }
    }
    set(flag);
    break;
  }
  }
}

void Element::set(bool value) {
  if (state != value)
  {

    state = value;
    for (auto output : outputs)
      output->calculate();
  }
}


bool CheckLoop (const Element& myself, const Element& where) {
  if (&where == &myself)
    return true;
  bool result = false;
  for (const Element* to_check : where.outputs)
  {
    if (CheckLoop(myself, *to_check))
    {

      return true;
    }
    return false;
  
  }
}
	Element& operator>> (Element& left, Element& right)
{
  if (CheckLoop(left, right))
  {
  
  throw std::runtime_error("loop detected");
  }

  bool input_connected{false};
  for (const auto input : right.inputs)
  {
    if (input == &left)
      input_connected = true;
  }
  if (!input_connected)
        right.inputs.push_back(&left);
  bool output_connected=false;
  for (const auto output : left.outputs)
  {
    if (output == &right)
      output_connected = true;
  }
  if (!output_connected)
  left.outputs.push_back(&right);
  if (!input_connected || !output_connected)
      right.calculate();
     return right;
}





}