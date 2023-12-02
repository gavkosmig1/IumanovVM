#include <std_lib_facilities.h>
#include "variable.h"
#include "token.h"
#include "grammar.h"


void replacement(string var, double val) //replaces variable's value with another
{
    for (int i = 0; i<(int)(var_table.size()); ++i) 
    {
        if (var_table[i].name == var) 
        {
            var_table[i].value = val;
            return;
        }
    }
}

double declaration (bool is_const)                                          //declares a variable
{
    Token t = ts.get();
    if (t.kind != name)
        error("name expected in declaration");

    string var = t.name;
    if (symbol_table.is_declared(var))
        error(var, " declared twice");

    t = ts.get();
    if (t.kind != '=')
        error("'=' missing in declaration of ", var);

    return symbol_table.define_name(var, expression(), is_const);
}

vector<Variable> var_table;
Symbol_table symbol_table(var_table);
                                                                            //Gets value from vector if name exists,
double Symbol_table::get_value(const string& s)                             //throws error otherwise

{
    for (size_t i = 0; i < Symbol_table::v.size(); ++i)
    {
        if (Symbol_table::v[i].name == s)
        {
            return Symbol_table::v[i].value;
        }
    }
    error("get: undefined name ", s);
}

bool Symbol_table::is_declared(const string& s)                             //Checks if name has already been declared
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

                                                                            //Sets value for name in vector if it is
                                                                            //a variable, if it's a constant or name
double Symbol_table::set_value(const string& s, double d)                   //doesn't exist, throws an error
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

                                                                            //Adds value into the vector of variables
                                                                            //Throws an error if the variable was
double Symbol_table::define_name(const string& var, double val, bool icg)   //Already declared

{
    if (Symbol_table::is_declared(var))
    {
        error(var, " declared twice");
    }
    Symbol_table::v.push_back(Variable{var, val, icg});
    return val;
}
