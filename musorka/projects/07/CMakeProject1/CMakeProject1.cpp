// CMakeProject1.cpp: определяет точку входа для приложения.
//

#include "CMakeProject1.h"

#include "Calculate.h"
#include "Const.h"
#include "Token.h"
#include "Token_stream.h"
#include "Variable.h"
#include "Variables.h"

#include "std_lib_facilities.h"

int main ()
try
{
    setlocale(LC_ALL, "Russian");
    Variables var_table;
    Token_stream ts;
    var_table.define_name("pi", 3.141592653589793);
    var_table.define_name("e", 2.718281828459045);

    print_help();
    calculator_start(var_table, ts, false);
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
