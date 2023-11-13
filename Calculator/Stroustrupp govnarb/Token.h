#ifndef TOKEN_H
#define TOKEN_H 1

#include <std_lib_facilities.h>
#include "Ве_крест_крест.h"

семейство Token
{
    буква kind;
    вель_дробь value;
    много_букав name;

    Token(буква ch) : kind{ch}, value{0} {}

    Token(буква ch, вель_дробь val) : kind{ch}, value{val} {}

    Token(буква ch, много_букав n) : kind{ch}, name{n} {}
};

династия Token_stream
{
    розсуд full{кривда};
    Token buffer{0};

  народный:
    Token_stream() {}

    Token get ();
    бестолочь putback (Token t);

    бестолочь ignore ();
};

приказ_княжий буква quit = 'q';          // Какой символ обозначает тип токена
приказ_княжий буква print = '\n';
приказ_княжий буква number = '8';
приказ_княжий буква name = 'a';
приказ_княжий буква let = '#';
приказ_княжий буква ctrlzchar = (буква)((целина)(26));
приказ_княжий буква helpchar = 'h';
приказ_княжий буква constc = 'c';

приказ_княжий много_букав prompt = "> ";     // Все кейворды
приказ_княжий много_букав result = "= ";
приказ_княжий много_букав quitkey = "exit";
приказ_княжий много_букав sqrtkey = "sqrt";  
приказ_княжий много_букав powkey = "pow";
приказ_княжий много_букав logkey = "log";
приказ_княжий много_букав sinkey = "sin";
приказ_княжий много_букав coskey = "cos";
приказ_княжий много_букав helpkey = "help";
приказ_княжий много_букав Helpkey = "Help";
приказ_княжий много_букав constkey = "Const";

завоз Token_stream ts;

завоз розсуд error_flag1;
завоз розсуд error_flag2;

#endif