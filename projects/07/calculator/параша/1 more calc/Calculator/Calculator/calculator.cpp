/*
 * "!!!PROGRAM_LOGIC AND GRAMMAR!!!"
 * .............................
 *
 * Instruction:
 *      Declaration
 *      Redefinition
 *      Expression
 *      Print
 *      Quit
 * Print:
 *      ';'
 *      '\n'
 * Quit:
 *      quit
 * Help:
 *      help
 * Declaration:
 *      "let" name = Expression
 *      "const" name = Expression
 * Redefinition:
 *      name = Expression
 * Expression:
 *      Term
 *      Expression - Term
 *      Expression + Term
 * Term:
 *      Primary
 *      Term * Primary
 *      Term / Primary
 *      Term % Primary
 * Primary:
 *      Number
 *      Number!
 *      ( Expression )
 *      ( Expression )!
 *      - Primary
 *      + Primary
 * Number:
 *      FloatingPointLiteral
 * .............................
 *
 *
 * "!!!PROGRAM_STRUCTURE!!!"
 * .....................
 *
 *
 * class Token
 *
 *
 * class Token_Stream
     *
     * void Token_stream:: putЬack ( Token t )
     * Token Token_stream:: qet ( )
     * void Token_stream:: ignore ( char c )
     *
 *
 * struct Variable
 *
 *
 * class Symbol_Table
 *
     *
     * double Symbol_Table::get(string s);
     * double Symbol_Table::set(string s, double d);
     * bool Symbol_Table::is_declared (string s);
     * double Symbol_Table::define_name (string var, double val, bool ch);
     *
 *
 * "CALCULATIONS_REALIZATIONS"
 *
     * int factorial(double n)
     * double primary ( Token_stream& ts, Symbol_Table& st )
     * double term ( Token_stream& ts, Symbol_Table& st )
     * double expression ( Token_stream& ts, Symbol_Table& st )
 *
 * "MAIN_LOOP"
 *
     * double declaration (bool changeable, Token_stream& ts, Symbol_Table& st)
     * double statement (Token_stream& ts, Symbol_Table& st)
     * void calculate (Token_stream& ts, Symbol_Table& st)
 *
 * void clean_up_mess (Token_stream& ts)
 * void print_help()
 *
 * int main ()
     * Token_stream ts ;
     * Symbol_Table st;
 * .....................
*/


#include "../../../Libraries/std_lib_facilities.h"
#include "token.h"
#include "variable.h"

int factorial(double n)
{
    if (int(n) != n || n < 0)
        error ("not valid factorial argument: ", n);
    int numb = 1;
    for (int i=1; i <= int(n); ++i)
    {
        numb *= i;
    }
    return numb;
}

double expression (Token_stream& ts, Symbol_Table& st);

double primary (Token_stream& ts, Symbol_Table& st)
{
  Token t = ts.get();
  switch (t.kind)
  {
  case '(':
  {
    double d = expression(ts, st);
    t = ts.get();
    if (t.kind != ')')
      error("'(' expected");
    Token t = ts.get();
    if (t.kind == '!')
        return factorial(d);
    ts.putback(t);
    return d;
  }

  case '-':
    return -primary(ts, st);
  case '+':
    return +primary(ts, st);

  case number:
  {
      double numb = t.value;
      Token t = ts.get();
      if (t.kind == '!')
          return factorial(numb);
      ts.putback(t);
      return numb;
  }

  case name:
  {
      string var = t.name;
      Token t = ts.get();
      if (t.kind == '=')
          return st.set(var, expression(ts, st));
      ts.putback(t);
      return st.get(var);
  }
  default:
    error("primary expected");
  }
}


double term (Token_stream& ts, Symbol_Table& st)
{
  double left = primary(ts, st);

  while (true)
  {
    Token t = ts.get();

    switch (t.kind)
    {
    case '*':
      left *= primary(ts, st);
      break;

    case '/':
    {
      double d = primary(ts, st);
      if (d == 0) error("divide by zero");
      left /= d;
      break;
    }

    case '%':
    {
        double dev = primary(ts, st);
        left = left - int(left / dev) * dev;
        break;
    }

    default:
      ts.putback(t);
      return left;
    }
  }
}


double expression (Token_stream& ts, Symbol_Table& st)
{
  double left = term(ts, st);

  while (true)
  {
    Token t = ts.get();

    switch (t.kind)
    {
    case '+':
      left += term(ts, st);
      break;

    case '-':
      left -= term(ts, st);
      break;

    default:
      ts.putback(t);
      return left;
    }
  }
}


double declaration (bool changeable, Token_stream& ts, Symbol_Table& st)
{
  Token t = ts.get();
  if (t.kind != name)
    error("name expected in declaration");

  string var = t.name;
  if (st.is_declared(var))
    error(var, " declared twice");

  t = ts.get();
  if (t.kind != '=')
    error("'=' missing in declaration of ", var);

  return st.define_name (var, expression(ts, st), changeable);
}


double statement (Token_stream& ts, Symbol_Table& st)
{
  Token t = ts.get();
  switch (t.kind)
  {
  case let:
    return declaration(true, ts, st);
  case constanta:
    return declaration(false, ts, st);
  default:
    ts.putback(t);
    return expression(ts, st);
  }
}


bool clean_up_mess (Token_stream& ts)
{
  return ts.ignore (print);
}


void print_help()
{
    cout << "-to write expression use chars:\n"
         << "\t+ - * / % () !\n"
         << "\tand warite ; after it to devide it from next expression\n"
         << "-to mind constant enter:\n"
         << "\tconst = your expression\n"
         << "-to mind variables enter:\n"
         << "\tlet = your expression\n"
         << "-to calculate your expression press 'enter':\n"
         << "-to exit from program enter:\n"
         << "\t -quit\n"
         << "-to get help inf enter:\n"
         << "\t -help"
         << endl;
}


void calculate (Token_stream& ts, Symbol_Table& st, bool no_promt=false)
{
  if (not no_promt)
      cout << prompt;
  while (true)
  try
  {
    Token t = ts.get();
    if (t.kind == quit) return;
    while (t.kind == print || t.kind == '\n')
    {
        if (t.kind == '\n')
            cout << prompt;
        t = ts.get();
    }
    if (t.kind == quit) return;
    if (t.kind == help) print_help();
    else
    {
        ts.putback(t);
        auto res = statement(ts, st);
        cout << result << res << endl;
    }
  }
  catch (runtime_error& e)
  {
    cerr << e.what() << endl;
    bool symb = clean_up_mess(ts);
    calculate(ts, st, symb);
    return;
  }
}


int main ()
try
{
  Symbol_Table st;
  Token_stream ts;

  st.define_name ("pi", 3.141592653589793, false);
  st.define_name ("e",  2.718281828459045, false);

  calculate(ts, st);
}
catch (exception& e)
{
  cerr << "exception: " << e.what() << endl;
  return 1;
}
catch (...)
{
  cerr << "Oops, unknown exception" << endl;
  return 2;
}
