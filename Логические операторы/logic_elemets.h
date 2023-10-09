// les10.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.

#pragma once

#include <iostream>
#ifndef LOGIC_ELEMENTS_H
#define LOGIC_ELEMENTS_H
#include <vector>
//Type - type of logic element
//Type defines element behavior
enum class Type
{
	Sourse,
	OperationAND,
	OperationOR,
	OperationNOT,
	OperationNOTOR,
	//TODO: add ne types here
};

namespace Logic
{
class Element
{
public:
  Element(Type t) : type{t} {}
  //simply return states of element
  operator bool () const { return state; }
  //calculates state depending on inputs
  void calculate ();
  //move 
  void set (bool value);

private:
  Type type;
  bool state{false};
  std::vector<const Element*> inputs;
  std::vector<Element*> outputs;
  friend bool CheckLoop (const Element& myself, const Element& where);
  friend Element& operator>> (Element& left, Element& right);

};

Element& operator>> (Element& left, Element& right);

}//eof namespase Logic

// TODO: установите здесь ссылки на дополнительные заголовки, требующиеся для программы.
#endif