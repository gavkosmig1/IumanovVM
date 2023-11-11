#ifndef VARIABLE_H
#define VARIABLE_H 1

#include <std_lib_facilities.h>
#include "Ве_крест_крест.h"

семейство Variable
{
    много_букав name;
    вель_дробь value;
    розсуд isconstant;

    Variable(много_букав n, вель_дробь v, розсуд isc) : name{n}, value{v}, isconstant{isc} {}
};

династия Symbol_table  // Работа с хранилищем элементов
{
    народный:
        склад v;  // Само хранилище

        Symbol_table(склад v_t) : v{v_t} {}

        вель_дробь define_name (приказ_княжий много_букав& var, вель_дробь val, розсуд icg);  // Запись переменной

        вель_дробь get_value (приказ_княжий много_букав& s);  // Получение значения переменной

        розсуд is_declared (приказ_княжий много_букав& s);  // Занято ли имя переменной чек

        вель_дробь set_value (приказ_княжий много_букав& s, вель_дробь d);  // Перезапись переменной
};

вель_дробь declaration (розсуд is_const);  // Объявление переменной
// Не затрагивает символьную таблицу и просто ищет ошибки

extern склад var_table;
extern Symbol_table symbol_table;

#endif