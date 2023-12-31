#include "variable.h"
#include "grammar.h"
#include "token.h"
#include <std_lib_facilities.h>

vector<Variable> var_table;
Symbol_table symbol_table(var_table);

double Symbol_table::get_value(const string& var_name)  // Получение значения переменной
{
    for (size_t i = 0; i < Symbol_table::v.size(); ++i)
    {
        if (Symbol_table::v[i].name == var_name)
        {
            return Symbol_table::v[i].value;
        }
    }
    error("Данная переменная не существует ", var_name);
}

bool Symbol_table::is_declared(const string& var_name)  // Занято ли имя переменной чек
{
    for (size_t i = 0; i < Symbol_table::v.size(); ++i)
    {
        if (Symbol_table::v[i].name == var_name)
        {
            return true;
        }
    }
    return false;
}

double Symbol_table::set_value(const string& s,
                               double d)  // Изменение значения переменной
{
    for (size_t i = 0; i < Symbol_table::v.size(); ++i)
    {
        if ((Symbol_table::v[i].name == s) && (!(Symbol_table::v[i].isconstant)))
        {
            Symbol_table::v[i].value = d;
            return d;
        }
    }
    error(s, " is constant");
}

double declaration (bool is_const)  // Объявление переменной
{
    Token t = ts.get();
    if (t.kind != name)
        error("Объявление без имени ");

    string var = t.name;
    if (symbol_table.is_declared(var))
        error(var, "Имя переменной занято ");

    t = ts.get();
    if (t.kind != '=')
        error("''=' забыт при объявлении переменной ", var);

    return symbol_table.define_name(var, expression(), is_const);
}

double Symbol_table::define_name(const string& var, double val,
                                 bool icg)  // Запись переменной
{
    if (Symbol_table::is_declared(var))
    {
        error(var, "Имя переменной занято ");
    }
    Symbol_table::v.push_back(Variable{var, val, icg});
    return val;
}