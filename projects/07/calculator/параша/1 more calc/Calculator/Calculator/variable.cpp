#include "../../../Libraries/std_lib_facilities.h"
#include "variable.h"

Variable::Variable (string n, double v, bool ch)
    : name{ n }, value{ v }, changeable{ ch }
{ }

double Symbol_Table::get(string s)
{
  for (int i = 0; i < var_table.size(); ++i)
    if (var_table[i].name == s)
      return var_table[i].value;

  error("get: undefined name ", s);
}

double Symbol_Table::set(string s, double d)
{
  for (int i = 0; i < var_table.size() - 1; ++i)
  {
    if (var_table[i].name == s)
    {
      if (!var_table[i].changeable)
          error ("try: change const variable ", s);
      var_table[i].value = d;
      return var_table[i].value;
    }
  }
  error("set: undefined name ", s);
}

bool Symbol_Table::is_declared (string s)
{
  for (int i = 0; i < var_table.size(); ++i)
    if (var_table[i].name == s) return true;
  return false;
}

double Symbol_Table::define_name (string var, double val, bool ch)
{
  if (is_declared(var))
    error(var, " declared twice");
  var_table.push_back (Variable{ var, val, ch});
  return val;
}
