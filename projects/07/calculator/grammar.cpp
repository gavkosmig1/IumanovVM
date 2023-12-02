#include "grammar.h"
#include "functions.h"
#include "variable.h"
#include <std_lib_facilities.h>

double statement ()  // Разделение входа на работу с переменными и числами
{
    Token t = ts.get();
    switch (t.kind)
    {
    case let:
        return declaration(false);
    case constc:
        return declaration(true);
    default:
        ts.putback(t);
        return expression();
    }
}

double expression ()  // Сложение и вычситание
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

double term ()  // Умножение, деление и остаток от деления
{
    double left = powterm();

    while (true)
    {
        Token t = ts.get();

        switch (t.kind)
        {
        case '*':
            left *= powterm();
            break;

        case '/':
        {
            double d = powterm();
            if (d == 0)
                error("division by zero");
            left /= d;
            break;
        }
        case '%':
        {
            double d = powterm();
            if (d == 0)
            {
                error("division by zero");
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

double powterm ()  // степени
{
    double left = primary();

    while (true)
    {
        Token t = ts.get();

        switch (t.kind)
        {
        case '^':
        {
            double d = primary();
            if (left == 0 && d == 0)
            {
                left = 1;
            }
            else
            {
                left = pow(left, d);
            }
            break;
        }
        default:
            ts.putback(t);
            return left;
        }
    }
}

double primary ()  // +- числа и скобки
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
            error("')' expected ");
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
        if (equation_mark_checker.kind == '=')
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

        error("primary expected ");
    }
}

void clean_up_mess ()  // не принимает ничего, пока не придет printkey
{
    ts.ignore();
}

void calculate ()  // Калькулирует
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
            else if (t.kind == helpchar)
            {
                std::cout << "You asked for help                                    \n";
                std::cout << "available operations: + - * / % ^                     \n";
                std::cout << "available functions:                                  \n";
                std::cout << "\"pow(a,b)\" the number a to the power of b           \n";
                std::cout << "\"sqrt(a)\" square root of a                          \n";
                std::cout << "\"sin(a)\" sinus of a; \"cos(a) cosinus of a          \n";
                std::cout << "\"log(a,b)\" logarithm of a on base b                 \n";
                std::cout << "\"#a = value\" declaring variable                     \n";
                std::cout << "\"const a = value\" declaring constant                \n";
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

double asignment (Token t)  // Изменение значения переменной
{
    if (t.kind != name)
        error("name lost in asignment ");

    string var = t.name;

    if (!symbol_table.is_declared(var))
        error(var, " is not declared ");

    for (size_t i = 0; i < symbol_table.v.size(); ++i)
    {
        if (symbol_table.v[i].name == var)
        {
            return symbol_table.set_value(var, expression());
        }
    }
    error(var, " is not declared ");
}
