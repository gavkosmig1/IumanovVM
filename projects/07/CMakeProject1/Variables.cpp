#include "std_lib_facilities.h"

#include "Const.h"
#include "RomanNumbers.h"
#include "Token.h"
#include "Token_stream.h"
#include "Variable.h"
#include "Variables.h"

double Variables::get_value(string s)
{
    for (int i = 0; i < var_table.size(); ++i)
        if (var_table[i].name == s)
            return var_table[i].value;

    error("get: undefined name ", s);
}

void Variables::set_value(string s, double d)
{
    for (int i = 0; i <= var_table.size(); ++i)
    {
        if (var_table[i].name == s)
        {
            var_table[i].value = d;
            return;
        }
    }

    error("set: undefined name ", s);
}

bool Variables::is_declared(string s)
{
    for (int i = 0; i < var_table.size(); ++i)
        if (var_table[i].name == s)
            return true;

    return false;
}

double Variables::define_name(string var, double val)
{
    if (is_declared(var))
        error(var, " declared twice");

    if (Is_roman_Num(var))
    {
        error("It is forbidden to designate Roman numbers as variables");
    }
    var_table.push_back(Variable(var, val));

    return val;
}

int Variables::length() { return var_table.size(); }

void Variables::clear() { var_table.clear(); }
