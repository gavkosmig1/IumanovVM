#include <std_lib_facilities.h>
#include "variable.h"
#include "token.h"
#include "grammar.h"

склад var_table;
Symbol_table symbol_table(var_table);

вель_дробь Symbol_table::get_value(приказ_княжий много_букав& var_name)  // Получение значения переменной
{
    для (мерило i = ноль; i < Symbol_table::v.size(); ++i)
    {
        коли (Symbol_table::v[i].name == var_name)
        {
            воздать Symbol_table::v[i].value;
        }
    }
    error("Данная переменная не существует ", var_name);
}

розсуд Symbol_table::is_declared(приказ_княжий много_букав& var_name)  // Занято ли имя переменной чек
{
    для (мерило i = ноль; i < Symbol_table::v.size(); ++i)
    {
        коли (Symbol_table::v[i].name == var_name)
        {
            воздать true;
        }
    }
    воздать false;
}

вель_дробь Symbol_table::set_value(приказ_княжий много_букав& var_name, вель_дробь new_d)  // Перезапись переменной
{
    для (мерило i = ноль; i < Symbol_table::v.size(); ++i)
    {
        коли(Symbol_table::v[i].name == var_name)
        {
            коли (Symbol_table::v[i].isconstant)
            {
                error("Нельзя изменить значение константы ");
            }
            отнюдь
            {
                Symbol_table::v[i].value = new_d;
                воздать new_d;
            }
        }
    error("Переменная не найдена ", var_name);
    }
}

вель_дробь declaration (розсуд is_const)  // Объявление переменной
{
    Token t = ts.get();
    коли (t.kind != name)
        error("Объявление без имени ");

    много_букав var = t.name;
    коли (symbol_table.is_declared(var))
        error(var, "Имя переменной занято ");

    t = ts.get();
    коли (t.kind != '=')
        error("''=' забыт при объявлении переменной ", var);

    воздать symbol_table.define_name(var, expression(), is_const);
}

вель_дробь Symbol_table::define_name(приказ_княжий много_букав& var, вель_дробь val, розсуд icg)  // Запись переменной
{
    коли (Symbol_table::is_declared(var))
    {
        error(var, "Имя переменной занято ");
    }
    Symbol_table::v.push_back(Variable{ var, val, icg });
    воздать val;
}