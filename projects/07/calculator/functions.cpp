#include <std_lib_facilities.h>
#include "functions.h"
#include "token.h"
#include "grammar.h"

double square_root()  // Квадратный корень
{
    Token t = ts.get();
    switch(t.kind)
    {
    case '(':
    {
        double d = expression();
        t = ts.get();
        if (t.kind != ')')
        {
            error("')' забыт в сквирте ");
        }
        if(d < 0)  // Негатив чек
        {
            error("Мнимый результат ");
        }
        return sqrt(d);
    }
    default:
        error("'(' забыт в сквирте ");
    }
}

double power()  // Степень
{
    Token t = ts.get();
    switch(t.kind)
    {
    case '(':
    {
        double l = expression();
        t = ts.get();
        if (t.kind != ','){
            error("',' забыт при возведении в степень ");
        }
        double r = expression();
        t = ts.get();
        if (t.kind != ')'){
            error("')'  забыт при возведении в степень ");
        }
        return pow(l,r);
    }
    default:
        error("'(' забыт при возведении в степень ");
    }
}

double logarithm()  // Логарифм
{
    Token t = ts.get();
    switch(t.kind)
    {
    case '(':
    {
        double l = expression();
        t = ts.get();
        if (t.kind != ','){
            error("',' забыт в логарифме ");
        }

        if(l < 0){
            error("отрицательное основание логарифма ");
        }
        else if(l == 1){
            error("основание логарифма не может быть равным '1'");
        }

        double r = expression();
        t = ts.get();
        if (t.kind != ')'){
            error("')' забыт в логарифме ");
        }

        if(r < 0){
            error("отрицательный аргумент логарифма ");
        }

        return (log(r))/(log(l));
    }
    default:
        error("'(' забыт в логарифме");
    }
}

double sine()  // Синус

{
    Token t = ts.get();
    switch(t.kind)
    {
    case '(':
    {
        double d = expression();
        t = ts.get();
        if (t.kind != ')')
        {
            error("')' забыт в синусе ");
        }
        return sin(d);
    }
    default:
        error("'(' забыт в синусе ");
    }
}

double cosine()  // Косинус

{
    Token t = ts.get();
    switch(t.kind)
    {
    case '(':
    {
        double d = expression();
        t = ts.get();
        if (t.kind != ')')
        {
            error("')' забыт в косинусе ");
        }
        return cos(d);
    }
    default:
        error("'(' expected");
    }
}