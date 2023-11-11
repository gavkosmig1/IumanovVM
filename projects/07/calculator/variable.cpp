#include <std_lib_facilities.h>
#include "variable.h"
#include "token.h"
#include "grammar.h"

vector<Variable> var_table;
Symbol_table symbol_table(var_table);

double Symbol_table::get_value(const string& s)  // Получение значения переменной

{
    for (size_t i = 0; i < Symbol_table::v.size(); ++i)
    {
        if (Symbol_table::v[i].name == s)
        {
            return Symbol_table::v[i].value;
        }
    }
    error("Данная переменная не существует ", s);
}

bool Symbol_table::is_declared(const string& s)  // Занято ли имя переменной чек
{
    for (size_t i = 0; i < Symbol_table::v.size(); ++i)
    {
        if (Symbol_table::v[i].name == s)
        {
            return true;
        }
    }
    return false;
}

double Symbol_table::set_value(const string& s, double d)  // Перезапись переменной
{
    for (size_t i = 0; i < Symbol_table::v.size(); ++i)
    {
        if ((!(Symbol_table::v[i].isconstant)) && (Symbol_table::v[i].name == s))
        {
            Symbol_table::v[i].value = d;
            return d;
        }
    }
    error("Переменная не найдена или является константой ", s);
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

double Symbol_table::define_name(const string& var, double val, bool icg)  // Запись переменной
{
    if (Symbol_table::is_declared(var))
    {
        error(var, "Имя переменной занято ");
    }
    Symbol_table::v.push_back(Variable{ var, val, icg });
    return val;
}