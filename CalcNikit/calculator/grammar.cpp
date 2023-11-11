#include <std_lib_facilities.h>
#include "grammar.h"
#include "variable.h"
#include "functions.h"

double statement () //0'st level of grammar (either expression or variable)
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

double expression () //1'st level of grammar that contains sum or subtraction
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

double term () //2'nd level of grammar that contains product, division or whole number division
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
                error("divide by zero");
            left /= d;
            break;
        }
        case '%':
        {
            double d = powterm();
            if (d == 0){
                error("divide by zero");
            }
            left -= d*int(left/d);
            break;
        }
        default:
            ts.putback(t);
            return left;
        }
    }
}

double powterm () //3'rd level of grammar that contains power operator
{
    double left = factterm();

    while (true)
    {
        Token t = ts.get();

        switch(t.kind)
        {
        case '^':
        {
            double d = factterm();
            if(left == 0 && d == 0)
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

double factterm() // 4'th level of grammar that contains factorial
{
    double left = primary();

    while (true)
    {
        Token t = ts.get();

        switch(t.kind)
        {
        case '!':
        {
            if(left < 0)
            {
                error("factorial isn't defined for negatives here");
            }
            else if(left - int(left) != 0){
                error("factorial isn't defined for non-integers here");
            }
            left = factorial(left);
            break;
        }
        default:
            ts.putback(t);
            return left;
        }
    }
}

double primary () //5'th level of grammar that contains either a literal value, variable or an expression within brackets
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
            //return get_value(t.name);
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

void clean_up_mess () //ignores everything in the input stream until printkey appears ('\n')
    {
     ts.ignore(); 
    }

void calculate () //performs the program cycle
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
                std::cout << "You have typed \"help\" or \"Help\"!\n\n";
                std::cout << "available operations:\n\n";
                std::cout << "sum:                                         \"a+b = c\"\n";
                std::cout << "substraction:                                \"a-b = c\"\n";
                std::cout << "product:                                     \"a*b = c\"\n";
                std::cout << "division:                                    \"a/b = c\"\n";
                std::cout << "mod division:                                \"a%b = c\"\n";
                std::cout << "raising to the power:                        \"a^b = c\"\n";
                std::cout << "calculating factorial of a positive integer:  \"a! = b\"\n\n";
                std::cout << "available functions:\n\n";
                std::cout << "raising to the power via function:   \"pow(a,b) = c\"\n";
                std::cout << "calculating square root of a number:  \"sqrt(a) = b\"\n";
                std::cout << "calculating sine:                      \"sin(a) = c\"\n";
                std::cout << "calculating cosine:                    \"cos(a) = b\"\n";
                std::cout << "calculating logarithm: a-base, b-val \"log(a,b) = c\"\n\n";
                std::cout << "to declare a variable use \"#a = value\"\n";
                std::cout << "to declare a constant use \"const a = value\"\n\n";
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

double asignment (Token t)  // Changes value of a variable
{
  if (t.kind != name)
    error("name expected in asignment");
  string va = t.name;
  if (!symbol_table.is_declared(va))
    error(va, " is not declared");
  for (size_t i = 0; i < (int)symbol_table.v.size(); ++i)
  {
    if (symbol_table.v[i].name == va)
    {
      return symbol_table.set_value(va, expression());
    }
  }
  error(va, " is not declared");
}
