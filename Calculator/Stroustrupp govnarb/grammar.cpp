#include <std_lib_facilities.h>
#include "grammar.h"
#include "variable.h"
#include "functions.h"

double statement ()  // 1) Разделение входа на объявление переменных, констант и вычисления
{
    Token t = ts.get();
    switch (t.kind)
    {
    case let:
        return declaration(false);  // Объявление переменной
    case constc:
        return declaration(true);   // Объявлеине константы
    default:
        ts.putback(t);
        return expression();        // Вычисления
    }
}

double expression ()                // 2) Плюс, минус
{
    double left = term();

    while (true)
    {
        Token t = ts.get();

        switch (t.kind)
        {
        case '+':
            left += term();
            break;
        case '-':
            left -= term();
            break;
        default:
            ts.putback(t);
            return left;
        }
    }
}

double term ()  // 3) Умножение, деление, остаток от деления
{
    double left = primary();

    while (true)
    {
        Token t = ts.get();

        switch (t.kind)
        {
        case '*':
            left *= primary();
            break;

        case '/':
        {
            double d = primary();
            if (d == 0)
                error("На ноль делить нельзя ");
            left /= d;
            break;
        }
        case '%':
        {
            double d = primary();
            if (d == 0){
                error("На ноль делить нельзя ");
            }
            left -= d * int(left / d);
            break;
        }
        default:
            ts.putback(t);
            return left;
        }
    }
}

double primary ()  // 4) Скобки, +- числа, переменные
{
    Token t = ts.get();
    switch (t.kind)
    {
    case '(':
    {
        double d = expression();
        t = ts.get();
        if (t.kind != ')')
        {
            error("')' expected");
        }
        return d;
    }

    case '-':
        return -primary();
    case '+':
        return +primary();

    case number:
        return t.value;

    case name:
    {
        Token equation_mark_checker = ts.get();
        if(equation_mark_checker.kind == '=')
        {
            return asignment(t);
        }
        else
        {
            ts.putback(equation_mark_checker);
            return symbol_table.get_value(t.name);
        }
    }
    default:

        error("primary expected");
    }
}

void clean_up_mess ()  // Скип строки
    {
     ts.ignore(); 
    }

void calculate () // Калькулирование
{
    std::cout << prompt;
    while (cin)
        try
        {
            Token t = ts.get();

            while (t.kind == print)
            {
                std::cout << prompt;
                t = ts.get();
            }

            if (t.kind == quit)
            {
                return;
            }

            else if(t.kind == helpchar)
            {
                std::cout << "Вы попросили о помощи                        \n";
                std::cout << "Доступные операции: +, -, *, /, %, ^         \n";
                std::cout << "pow(a,b), sqrt(a), sin(a), cos(a), log(a,b)  \n";
                std::cout << "Объявление переменных через #имя = значение  \n";
                std::cout << "А констант через const имя = значение        \n";
                ts.ignore();
            }
            else
            {
                ts.putback(t);
                cout << result << statement() << endl;
            }
        }
        catch (runtime_error& e)
        {
            cerr << e.what() << endl;
            clean_up_mess();
        }
}

double asignment (Token t)  // Изменение значения существующей переменной
{
    if (t.kind != name)
        error("Имя требуется для изменения значения ");
    return symbol_table.set_value(t.name, expression());
}