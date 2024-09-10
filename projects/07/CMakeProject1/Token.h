#ifndef Token_h
#define Token_h

#include "std_lib_facilities.h"

struct Token
{
    char kind;
    double value;
    string name;

    Token(char ch);

    Token(char ch, string nam);

    Token(char ch, double val);
};

#endif
