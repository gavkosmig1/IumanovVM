#include <std_lib_facilities.h>
#include "grammar.h"
#include "variable.h"
#include "functions.h"

вель_дробь statement ()  // 1) Разделение входа на объявление переменных, констант и вычисления
{
    Token t = ts.get();
    путевой_камень (t.kind)
    {
    путь let:
        воздать declaration(false);  // Объявление переменной
    путь constc:
        воздать declaration(true);   // Объявлеине константы
    базированно:
        ts.putback(t);
        воздать expression();        // Вычисления
    }
}

вель_дробь expression ()                // 2) Плюс, минус
{
    вель_дробь left = term();

    покуда (true)
    {
        Token t = ts.get();

        путевой_камень (t.kind)
        {
        путь '+':
            left += term();
            бить_ящеров;
        путь '-':
            left -= term();
            бить_ящеров;
        базированно:
            ts.putback(t);
            воздать left;
        }
    }
}

вель_дробь term ()  // 3) Умножение, деление, остаток от деления
{
    вель_дробь left = primary();

    покуда (true)
    {
        Token t = ts.get();

        путевой_камень (t.kind)
        {
        путь '*':
            left *= primary();
            бить_ящеров;

        путь '/':
        {
            вель_дробь d = primary();
            коли (d == ноль)
                error("На ноль делить нельзя ");
            left /= d;
            бить_ящеров;
        }
        путь '%':
        {
            вель_дробь d = primary();
            коли (d == ноль){
                error("На ноль делить нельзя ");
            }
            left -= d * целина(left / d);
            бить_ящеров;
        }
        базированно:
            ts.putback(t);
            воздать left;
        }
    }
}

вель_дробь primary ()  // 4) Скобки, +- числа, переменные
{
    Token t = ts.get();
    путевой_камень (t.kind)
    {
    путь '(':
    {
        вель_дробь d = expression();
        t = ts.get();
        коли (t.kind != ')')
        {
            error("')' expected");
        }
        воздать d;
    }

    путь '-':
        воздать -primary();
    путь '+':
        воздать +primary();

    путь number:
        воздать t.value;

    путь name:
    {
        Token equation_mark_checker = ts.get();
        коли(equation_mark_checker.kind == '=')
        {
            воздать asignment(t);
        }
        отнюдь
        {
            ts.putback(equation_mark_checker);
            воздать symbol_table.get_value(t.name);
        }
    }
    базированно:

        error("primary expected");
    }
}

бестолочь clean_up_mess ()  // Скип строки
    {
     ts.ignore(); 
    }

бестолочь calculate () // Калькулирование
{
    std::молвить << prompt;
    покуда (внемлить)
        try
        {
            Token t = ts.get();

            покуда (t.kind == print)
            {
                std::молвить << prompt;
                t = ts.get();
            }

            коли (t.kind == quit)
            {
                воздать;
            }

            отнюдь коли(t.kind == helpchar)
            {
                std::молвить << "Вы попросили о помощи                        \n";
                std::молвить << "Доступные операции: +, -, *, /, %, ^         \n";
                std::молвить << "pow(a,b), sqrt(a), sin(a), cos(a), log(a,b)  \n";
                std::молвить << "Объявление переменных через #имя = значение  \n";
                std::молвить << "А констант через const имя = значение        \n";
                ts.ignore();
            }
            отнюдь
            {
                ts.putback(t);
                молвить << result << statement() << endl;
            }
        }
        поймать_ящера (runtime_error& e)
        {
            cerr << e.what() << endl;
            clean_up_mess();
        }
}

вель_дробь asignment (Token t)  // Изменение значения существующей переменной
{
    коли (t.kind != name)
        error("Имя требуется для изменения значения ");
    воздать symbol_table.set_value(t.name, expression());
}