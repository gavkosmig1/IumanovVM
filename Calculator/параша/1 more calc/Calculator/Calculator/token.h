#ifndef TOKEN_H
#define TOKEN_H

#include "../../../Libraries/std_lib_facilities.h"

struct Token
{
  char kind;
  double value;
  string name;

  Token (char ch);
  Token (char ch, double val);
  Token (char ch, string nname);
};


class Token_stream
{
    bool full {false};
    Token buffer {'\0'};

public:
  Token_stream() {};
  Token get ();
  void putback (Token t);
  bool ignore (char c);
};

constexpr char print = ';';
constexpr char number = '8';
constexpr char name = 'a';
constexpr char quit = 'q';
constexpr char help = 'h';
constexpr char let = 'L';
constexpr char constanta = 'C';

const string quitkey = "quit";
const string helpkey = "help";
const string prompt = "> ";
const string result = "= ";
const string declkey = "let";
const string constkey = "const";

#endif // TOKEN_H
