#ifndef VARIABLE_H
#define VARIABLE_H 1

#include <std_lib_facilities.h>

struct Variable
{
    string name;
    double value;
    bool isconstant;

    Variable(string n, double v, bool isc) : name{n}, value{v}, isconstant{isc} {}
};

class Symbol_table  // Работа с хранилищем элементов
{
    public:
        vector<Variable> v;  // Само хранилище

        Symbol_table(vector<Variable> v_t) : v{v_t} {}

        double define_name (const string& var, double val, bool icg);  // Запись переменной

        double get_value (const string& s);  // Получение значения переменной

        bool is_declared (const string& s);  // Занято ли имя переменной чек

        double set_value (const string& s, double d);  // Перезапись переменной
};

double declaration (bool is_const);  // Объявление переменной
// Не затрагивает символьную таблицу и просто ищет ошибки

extern vector<Variable> var_table;
extern Symbol_table symbol_table;

#endif