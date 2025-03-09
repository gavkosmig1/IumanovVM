#ifndef Token_stream_h
#define Token_stream_h

#include "Token.h"
#include "std_lib_facilities.h"
#include <conio.h>
#include <stdio.h>

class Token_stream
{
    string s = "";
    bool full{false};
    Token buffer{'\0'};

  public:
    Token_stream() {}

    Token get ();            // Получение токена со входа
    void putback (Token t);  // Записывает токен в буфер

    bool ignore (char);
};

#endif
