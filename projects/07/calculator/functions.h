#ifndef FUNCTIONS_H
#define FUNCTIONS_H 1

#include "std_lib_facilities.h"

// очев
double square_root ();
double power ();
double logarithm ();
double sine ();
double cosine ();

string toRoman (const int& number);  // Возвращает римское значение чисел
int RomanValue (const char& r);      // Возвращает численное значение римких буков
int ToDecimal (const string& str);   // Переводит римское число в десятичное

#endif