#include<iostream>
#include"logic_elemets.h"
#include"std_lib_facilities.h"
int main ()
try
{
	using namespace Logic;
  Element and1{Type::OperationAND};
  Element or1{Type::OperationOR};
  Element src1{Type::Sourse};
  src1 >> and1 >> or1;
  or1 >> and1;

  if (src1)
    cout << "src1: true" << endl;
  else
    cout << "src1: false" << endl;
  return 0;

}
catch (...)
{
}