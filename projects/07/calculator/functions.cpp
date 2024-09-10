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

string toRoman (int& number)  // Возвращает римское значение чисел
{
    if ((number < 1) || (number > 3999))
        error("Can't convert the number to Roman");
    string result;
    int num[] = {1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000};
    string sym[] = {"I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D", "CM", "M"};
    int i = 12;
    while (number > 0)
    {
        int div = number / num[i];
        number = number % num[i];
        while (div--)
        {
            result += sym[i];
        }
        i--;
    }
    return result;
}

int RomanValue (const char& r)  // Возвращает численное значение римких буков
{
    if (r == 'I')
        return 1;
    if (r == 'V')
        return 5;
    if (r == 'X')
        return 10;
    if (r == 'L')
        return 50;
    if (r == 'C')
        return 100;
    if (r == 'D')
        return 500;
    if (r == 'M')
        return 1000;
    error("Can't convert the number to Decimal");
}

int ToDecimal (const string& str)  // Переводит римское число в десятичное
{
    int res = 0;

    for (size_t i = 0; i < str.length(); i++)
    {
        int s1 = RomanValue(str[i]);

        if (i + 1 < str.length())  // Чтобы не обратиться сверх числа
        {
            int s2 = RomanValue(str[i + 1]);

            if (s1 >= s2)
            {
                res = res + s1;
            }
            else
            {
                res = res + s2 - s1;
                i++;
            }
        }
        else
        {
            res = res + s1;
        }
    }
    return res;
}