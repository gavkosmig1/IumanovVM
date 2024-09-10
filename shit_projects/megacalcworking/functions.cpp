#include "functions.h"
#include "grammar.h"
#include "token.h"

double square_root ()  // Квадратный корень
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
            error("')' lost in sqrt ");
        }
        if (d < 0)
        {
            error("Imaginary result ");
        }
        return sqrt(d);
    }
    default:
        error("'(' lost on sqrtr ");
    }
}

double power ()  // Степень
{
    Token t = ts.get();
    switch (t.kind)
    {
    case '(':
    {
        double l = expression();
        t = ts.get();
        if (t.kind != ',')
        {
            error("',' lost in pow ");
        }
        double r = expression();
        t = ts.get();
        if (t.kind != ')')
        {
            error("')' lost in pow ");
        }
        return pow(l, r);
    }
    default:
        error("'(' lost in pow ");
    }
}

double logarithm ()  // Логарифм
{
    Token t = ts.get();
    switch (t.kind)
    {
    case '(':
    {
        double l = expression();
        t = ts.get();
        if (t.kind != ',')
        {
            error("',' lost in log ");
        }

        if (l < 0)
        {
            error("negative logarithm base ");
        }
        else if (l == 1)
        {
            error("logarithm base can't be 1");
        }

        double r = expression();
        t = ts.get();
        if (t.kind != ')')
        {
            error("')' lost in log ");
        }

        if (r < 0)
        {
            error("negative logarithm value ");
        }

        return (log(r)) / (log(l));
    }
    default:
        error("'(' lost in log ");
    }
}

double sine ()  // синус
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
            error("')' lost in sin ");
        }
        return sin(d);
    }
    default:
        error("'(' lost in sin ");
    }
}

double cosine ()  // косинус
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
            error("')' lost in cos ");
        }
        return cos(d);
    }
    default:
        error("'(' lost in cos ");
    }
}
