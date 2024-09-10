#include "functions.h"
#include "grammar.h"
#include "token.h"
#include "variable.h"

int main ()
try
{
    std::cout << "Calculator by Yumanov Vasiliy gavkosmig   \n";
    std::cout << "Type \"help\" to ask for help             \n";

    symbol_table.define_name("pi", 3.141592653589793, true);  // Pi
    symbol_table.define_name("e", 2.718281828459045, true);   // Euler's number
    symbol_table.define_name("k", 1000, true);                // 1000

    calculate();
}
catch (exception& e)
{
    cerr << "exception: " << e.what() << endl;
    return 1;
}
catch (...)
{
    cerr << "Oops, unknown exception " << endl;
    return 2;
}