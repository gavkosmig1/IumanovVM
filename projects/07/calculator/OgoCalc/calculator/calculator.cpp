#include <std_lib_facilities.h>
#include "functions.h"
#include "grammar.h"
#include "token.h"
#include "variable.h"

int main ()
try
{
    std::cout << "Hello, welcome to the calculator!\n";
    std::cout << "Type \"help\" or \"Help\" if you want to know available features\n\n";

    symbol_table.define_name("pi", 3.141592653589793, true); // Pi
    symbol_table.define_name("e", 2.718281828459045, true);  // Euler's number
    symbol_table.define_name("k", 1000, true);               // k = 1000 from Stroustroop's task

    calculate();                          // Activate the calculator cycle
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