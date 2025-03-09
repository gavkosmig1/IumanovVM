#include <std_lib_facilities.h>
#include "functions.h"
#include "token.h"
#include "grammar.h"
                     //Checks if the expression in brackets are correct
double square_root() //after "sqrt" key was typed and calculates it
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
            error("')' expected");
        }
        if(d < 0) //Checks if the number inside a root is negative
        {
            error("can't get a square root of a negative number");
        }
        return sqrt(d);
    }
    default:
        error("'(' expected");
    }
}

               //Checks if two expressions within the brackets that are separated by a comma are correct
double power() //after "pow" key was typed and calculates it
{
    Token t = ts.get();
    switch(t.kind)
    {
    case '(':
    {
        double l = expression();
        t = ts.get();
        if (t.kind != ','){
            error("',' expected");
        }
        double r = expression();
        t = ts.get();
        if (t.kind != ')'){
            error("')' expected");
        }
        return pow(l,r);
    }
    default:
        error("'(' expected");
    }
}
 
                   //Checks if two expressions within the brackets that are separated by a comma are correct
double logarithm() //after "log" key was typed and calculates it

{
    Token t = ts.get();
    switch(t.kind)
    {
    case '(':
    {
        double l = expression();
        t = ts.get();
        if (t.kind != ','){
            error("',' expected");
        }

        if(l < 0){
            error("logarithm indicator can't be a negative number");
        }
        else if(l == 1){
            error("logarithm indicator can't be equal to '1'");
        }

        double r = expression();
        t = ts.get();
        if (t.kind != ')'){
            error("')' expected");
        }

        if(r < 0){
            error("logarithm value can't be a negative number");
        }

        return (log(r))/(log(l));
    }
    default:
        error("'(' expected");
    }
}

               //Checks if the expression in brackets are correct
double sine()  //after "sine" key was typed and calculates it

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
            error("')' expected");
        }
        return sin(d);
    }
    default:
        error("'(' expected");
    }
}

                 //Checks if the expression in brackets are correct
double cosine()  //after "cosine" key was typed and calculates it

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
            error("')' expected");
        }
        return cos(d);
    }
    default:
        error("'(' expected");
    }
}

int factorial(int n) //just calculates factorial
{
    if(n == 0) return 1;
    int ans = 1;
    for(int i = 1; i <= n; i++) ans *= i;
    return ans;
}
