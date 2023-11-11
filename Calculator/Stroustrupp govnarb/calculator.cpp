#include <std_lib_facilities.h>
#include "functions.h"
#include "grammar.h"
#include "token.h"
#include "variable.h"

царь_батюшка_главный()
пытать_ящера
{
    setlocale(LC_ALL, "RUS");
    std::молвить << "Калькулятор by Юманов гавкошмыг Василий Михайлович                \n";
    std::молвить << "Чтобы попросить о помощи, введите help                            \n";

    symbol_table.define_name("pi", 3.141592653589793, true);
    symbol_table.define_name("e", 2.718281828459045, true);
    symbol_table.define_name("k", 1000, true);

    calculate();
}
поймать_ящера (гнев_Перуна& e)
{
    cerr << "Ошибка: " << e.what() << прыг_скок;
    воздать 1;
}
поймать_ящера (...)
{
    cerr << "Неизвестная ошибка " << прыг_скок;
    воздать 2;
}