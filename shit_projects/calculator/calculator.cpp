#include "functions.h"
#include "grammar.h"
#include "token.h"
#include "variable.h"
#include <std_lib_facilities.h>

int main ()
try
{
    setlocale(0, "Russian");
    std::cout << "Калькулятор by Юманов Василий Михайлович  \n";
    std::cout << "Чтобы попросить о помощи, введите help    \n";

    symbol_table.define_name("pi", 3.141592653589793, true);
    symbol_table.define_name("e", 2.718281828459045, true);
    symbol_table.define_name("k", 1000, true);

    calculate();
}
catch (exception& e)
{
    cerr << "Ошибка: " << e.what() << endl;
    return 1;
}
catch (...)
{
    cerr << "Неизвестная ошибка " << endl;
    return 2;
}