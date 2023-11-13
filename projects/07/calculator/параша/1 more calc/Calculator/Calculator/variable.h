#ifndef VARIABLE_H
#define VARIABLE_H

#include "../../../Libraries/std_lib_facilities.h"
#include "token.h"

struct Variable
{
  string name;
  double value;
  bool changeable;

  Variable (string n, double v, bool ch);
};


class Symbol_Table
{
public:
    vector <Variable> var_table{ };

    double get(string s);
    double set(string s, double d);
    bool is_declared (string s);
    double define_name (string var, double val, bool ch);

    Symbol_Table() {}
};

#endif // VARIABLE_H
