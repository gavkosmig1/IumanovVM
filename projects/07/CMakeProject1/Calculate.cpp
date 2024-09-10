#include "std_lib_facilities.h"

#include "Calculate.h"
#include "Const.h"
#include "RomanNumbers.h"
#include "RomanNumsConvert.h"
#include "Token.h"
#include "Variable.h"
#include <cmath>

Variables var_table;
Token_stream ts;
bool in_roman_mode = false;

void print_help ()
{
    cout << "-to write expression use chars:\n"
         << "\t+ - * / % () exp() arcsin() tg() ctg()\n"
         << "\tand write ; after it to devide it from next expression\n"
         << "-to mind variables enter:\n"
         << "\tlet = your expression\n"
         << "-to put a roman mod:\n"
         << "\twrite 'Roman'\n"
         << "-to put a decimal mod:\n"
         << "\twrite 'Decimal'\n"
         << "-to calculate your expression press 'enter':\n"
         << "-to exit from program enter:\n"
         << "\t -quit\n"
         << "-to get help inf enter:\n"
         << "\t -help" << endl;
}

double primary ()  // 3: +-числа, переменные, кейворды, dr hq скобки
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
            if (t.kind == '\n' || t.kind == ';')
            {
                ts.putback(t);
                return d;
            }
            error("')' expected");
        }
        return d;
    }

    case '-':
        return -primary();
    case '+':
        return +primary();

    case number:
        if (in_roman_mode)
        {
            error("Decimal numbers in Roman mode");
        }
        return t.value;

    case decimal:
        ts.putback(decimal);  // !!
        return 0;

    case roman:
        ts.putback(roman);
        return 0;

    case name:
        if (var_table.is_declared(t.name))
        {
            return var_table.get_value(t.name);
        }
        else
        {
            if (Is_roman_Num(t.name))
            {
                if (in_roman_mode)
                {
                    return arabic(t.name);
                }
                else
                {
                    error("Roman numbers in Decimal mode");
                }
            }
            else
            {
                return var_table.get_value(t.name);
            }
        }
    case help:
    {
        ts.putback(help);
        return 0;
    }
    case quit:
    {
        ts.putback(quit);
        return 0;
    }
    case '\n':
    case ';':
    {
        ts.putback(t);
        return 0;
    }
    case ')':
    {
        ts.putback(';');
        return 0;
    }
    case e:
        return pow(2.718281828459045, expression());
    case tang:
    {
        double d = expression();
        if (cos(d) == 0)
            error("ctangens is not defined");
        return tan(d);
    }
    case ctang:
    {
        double d = expression();
        if (sin(d) == 0)
            error("tangens is not defined");
        return 1 / tan(d);
    }
    case arcsinu:
        return asin(expression());
    default:
        error("primary expected");
    }
}

double term ()  // 2: */% dr hq )
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
                error("divide by zero");
            left /= d;
            break;
        }
        case '%':
        {
            double d = primary();
            if (d == 0)
                error(" % : ������� �� ���� ");
            left = fmod(left, d);
            break;
        }
        case decimal:

            ts.putback(decimal);
            return left;
        case roman:

            ts.putback(roman);
            return left;
        case 'h':
        {
            ts.putback(help);
            return left;
        }
        case 'q':
        {
            ts.putback(quit);
            return left;
        }
        case ')':
        {
            ts.putback(';');
            return left;
        }
        default:
            ts.putback(t);
            return left;
        }
    }
}

double expression ()  // 1: +- dr hq )
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

        case decimal:
            ts.putback(decimal);
            return left;

        case roman:
            ts.putback(roman);
            return left;

        case 'h':
        {
            ts.putback(help);
            return left;
        }
        case 'q':
        {
            ts.putback(quit);
            return left;
        }
        case ')':
        {
            ts.putback(';');
            return left;
        }
        default:
            ts.putback(t);
            return left;
        }
    }
    return left;  // ??
}

double declaration ()  // 0.1: Объявление переменной
{
    Token t = ts.get();

    if (t.kind != name)
        error("name expected in declaration");

    string var = t.name;
    if (var_table.is_declared(var))
        error(var, " declared twice");

    t = ts.get();
    if (t.kind != '=')
        error("'=' missing in declaration of ", var);

    return var_table.define_name(var, expression());
}

double statement ()  // 0: Разделение входа на вычисления и объявление переменных
{
    Token t = ts.get();
    switch (t.kind)
    {
    case let:
        return declaration();
    default:
        ts.putback(t);
        return expression();
    }
}

bool clean_up_mess (Token_stream& ts) { return ts.ignore(print); }

void calculator_start (Variables _var_table, Token_stream _ts, bool no_promt = false)
{
    var_table = _var_table;
    ts = _ts;

    if (not no_promt)
        cout << prompt;

    while (true)
        try
        {
            Token t = ts.get();
            if (t.kind == quit)
                return;
            while (t.kind == print || t.kind == '\n')
            {
                if (t.kind == '\n')
                    cout << prompt;
                t = ts.get();
            }  // !!

            if (t.kind == roman)
            {
                cout << "-Roman mode activated" << endl;
                in_roman_mode = true;
            }
            else if (t.kind == decimal)
            {
                cout << "-Decimal mode activated" << endl;
                in_roman_mode = false;
            }
            else if (t.kind == help)
                print_help();
            else
            {
                ts.putback(t);
                if (in_roman_mode)
                {
                    cout << result << DecToRoman(statement()) << endl;
                }
                else
                {
                    cout << result << statement() << endl;
                }
            }
        }
        catch (runtime_error& e)
        {
            cerr << e.what() << endl;
            try
            {
                bool symb = clean_up_mess(ts);
                calculator_start(var_table, ts, symb);
                return;
            }
            catch (exception& e)
            {
                cerr << e.what() << endl;
                return;
            }
        }
        catch (exception& e)
        {
            cerr << e.what() << endl;
            return;
        }
}