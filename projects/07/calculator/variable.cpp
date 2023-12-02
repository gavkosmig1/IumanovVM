#include "variable.h"
#include "grammar.h"
#include "token.h"

vector<Variable> var_table;
Symbol_table symbol_table(var_table);

double declaration (bool is_const)  // объявление переменной
{
    Token t = ts.get();
    if (t.kind != name)
        error("name lost in declaration ");

    string var = t.name;
    if (symbol_table.is_declared(var))
        error(var, " already exists ");

    t = ts.get();
    if (t.kind != '=')
        error("'=' lost in declaration of ", var);

    return symbol_table.define_name(var, expression(), is_const);
}

double Symbol_table::define_name(const string& var, double val, bool icg)  // Запись переменной
{
    Symbol_table::v.push_back(Variable{var, val, icg});
    return val;
}

double Symbol_table::get_value(const string& s)  // Получение значения существующей переменной
{
    for (size_t i = 0; i < Symbol_table::v.size(); ++i)
    {
        if (Symbol_table::v[i].name == s)
        {
            return Symbol_table::v[i].value;
        }
    }
    error("getting value of non-existent variable ", s);
}

bool Symbol_table::is_declared(const string& s)  // Объявлена ли переменная чек
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

double Symbol_table::set_value(const string& s, double d)  // Устанавливает значение существующей переменной
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
