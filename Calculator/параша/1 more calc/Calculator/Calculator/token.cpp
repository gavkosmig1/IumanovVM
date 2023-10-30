#include "token.h"
#include "../../../Libraries/std_lib_facilities.h"

Token::Token (char ch)
  : kind{ ch }, value{ 0 }
{ }

Token::Token (char ch, double val)
  : kind{ ch }, value{ val }
{ }

Token::Token (char ch, string nname)
  : kind{ ch }, name{ nname }
{ }

void Token_stream::putback (Token t)
{
  if (full)
    error("putback() into a full buffer");

  buffer = t;
  full = true;
}

Token Token_stream::get ()
{
  if (full)
  {
    full = false;
    return buffer;
  }

  char ch;
  cin.get(ch);
  if (not cin)
      return Token { quit };
  while (ch != '\n' && ch != '\r' && isspace(ch))
  {
      cin.get(ch);
      if (not cin)
          return Token { quit };
  }
  switch (ch)
  {
  case '(':
  case ')':
  case '+':
  case '-':
  case '*':
  case '/':
  case '%':
  case '!':
  case print:
  case '\n':
  case '=':
    return Token{ ch };
  case '\r':
      error("Bad token");

  case '.':
  case '0': case '1': case '2': case '3': case '4':
  case '5': case '6': case '7': case '8': case '9':
  {
    cin.putback(ch);
    double val;
    cin >> val;
    return Token{ number, val };
  }

  default:
    if (isalpha(ch) || ch == '_')
    {
      string s;
      s += ch;
      while (cin.get(ch) &&
             (isalpha(ch) || isdigit(ch) || ch == '_'))
        s += ch;
      cin.putback(ch);

      if (s == quitkey) return Token{ quit };
      if (s == helpkey) return Token{ help };
      if (s == declkey) return Token{ let };
      if (s == constkey) return Token { constanta };
      return Token{ name, s };
    }
    error("Bad token");
  }
}

bool Token_stream::ignore (char c)
{
  if (full && buffer.kind == c)
  {
    full = false;
    return true;
  }
  if (full && buffer.kind == '\n')
  {
    full = false;
    return false;
  }
  full = false;
  char ch;
  while (cin.get(ch))
  {
      if (ch == c)
          return true;
      if (ch == '\n')
          return false;
  }
}
