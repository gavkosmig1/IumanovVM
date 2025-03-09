#ifndef Variables_h
#define Variables_h

#include "Token_stream.h"
#include "Variable.h"
#include "std_lib_facilities.h"

class Variables
{
    vector<Variable> var_table;

  public:
    double get_value (string s);

    void set_value (string s, double d);

    bool is_declared (string s);

    double define_name (string var, double val);

    int length ();

    void clear ();
};

#endif
