#include "std_lib_facilities.h"

#include "Const.h"
#include "Token_stream.h"
#include <conio.h>

void Token_stream::putback(Token t)  // Записывает токен в буфер
{
    if (full)
        error("putback() into a full buffer");

    buffer = t;
    full = true;
}

Token Token_stream::get()  // Получение токена со входа
{
    if (full)  // Опустошение буфера
    {
        full = false;
        return buffer;
    }

    char ch;
    cin.get(ch);
    if (!cin || ch == '\x1a')  // ctrlz char
    {
        throw exception("Critacal token");
    }

    while (ch != '\n' && ch != '\r' && isspace(ch))  // скип пробелов
    {
        cin.get(ch);
        if (!cin)
            return Token{quit};
    }
    switch (ch)
    {
    case '(':
    case ')':
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case '!':
    case print:
    case '\n':
    case '=':
        return Token{ch};
    case '\r':
        error("Bad token");
    case '.':
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    {  // считывание числа полностью
        cin.putback(ch);
        double val;
        cin >> val;
        return Token{number, val};
    }

    default:  // кейворды
        if (isalpha(ch) || ch == '_')
        {
            string s;
            s += ch;
            while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_'))
                s += ch;
            cin.putback(ch);

            if (s == roman_mode)
                return Token{roman};
            if (s == dec_mode)
                return Token{decimal};
            if (s == exponenta)
                return Token{e};
            if (s == tg)
                return Token{tang};
            if (s == ctg)
                return Token{ctang};
            if (s == arcsin)
                return Token{arcsinu};
            if (s == helpkey)
                return Token{help};
            if (s == quitkey)
                return Token{quit};
            if (s == declkey)
                return Token{let};
            if (s == constkey)
                return Token{constanta};
            return Token{name, s};
        }
        error("Bad token");
    }
}

bool Token_stream::ignore(char c)
{
    if (full && buffer.kind == c)
    {
        full = false;
        return true;
    }
    if (full && buffer.kind == '\n')
    {
        full = false;
        return false;
    }
    full = false;
    char ch;
    while (cin.get(ch))
    {
        if (ch == '\x1a')
        {
            throw exception("Critacal token");
        }
        if (ch == c)
            return true;
        if (ch == '\n')
            return false;
    }
}
