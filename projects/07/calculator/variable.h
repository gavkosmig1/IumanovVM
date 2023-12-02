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

class Symbol_table  // Хранилище переменных
{
  public:
    vector<Variable> v;  // Вектор с переменными

    Symbol_table(vector<Variable> v_t) : v{v_t} {}

    double get_value (const string& s);  // Получение значения существующей переменной
    bool is_declared (const string& s);  // Объявлена ли переменная чек
    double set_value (const string& s, double d);  // Устанавливает значение существующей переменной
    double define_name (const string& var, double val, bool icg);  // Запись переменной
};

double declaration (bool is_const);  // объявление переменной

extern vector<Variable> var_table;
extern Symbol_table symbol_table;

#endif