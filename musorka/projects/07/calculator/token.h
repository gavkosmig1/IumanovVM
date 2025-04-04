#ifndef TOKEN_H
#define TOKEN_H 1

#include "std_lib_facilities.h"

struct Token
{
    char kind;
    double value;
    string name;

    Token(char ch) : kind{ch}, value{0} {}

    Token(char ch, double val) : kind{ch}, value{val} {}

    Token(char ch, string n) : kind{ch}, name{n} {}
};

class Token_stream
{
    bool full{false};
    Token buffer{0};

  public:
    Token_stream() {}

    Token get ();
    void putback (Token t);

    void ignore ();
};

// то, что хранится как тип токена
const char quit = 'q';
const char print = '\n';
const char number = '8';
const char name = 'a';
const char let = '#';
const char ctrlzchar = (char)((int)(26));
const char helpchar = 'h';
const char constc = 'c';

const char rome = 'r';
const char deci = 'd';

// то, что выводится / вводится
const string prompt = "> ";
const string result = "= ";
const string quitkey = "exit";
const string sqrtkey = "sqrt";
const string powkey = "pow";
const string logkey = "log";
const string sinkey = "sin";
const string coskey = "cos";
const string helpkey = "help";
const string Helpkey = "Help";
const string constkey = "const";

const string romekey = "Roman";
const string decikey = "Decimal";

extern Token_stream ts;

extern bool error_flag1;
extern bool error_flag2;

#endif