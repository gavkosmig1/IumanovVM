#include "token.h"
#include "functions.h"
#include <std_lib_facilities.h>

void Token_stream::putback(Token t)  // Сохарняет токен, чтобы тот не потерялся
{
    if (full)
        error("putback() into a full buffer ");

    buffer = t;
    full = true;
}

Token Token_stream::get()  // Считывание входа
{
    if (full)  // Первым делом проверить буфер
    {
        full = false;
        return buffer;
    }

    char ch = ' ';
    while (isspace(ch))  // скип пробелов
    {
        ch = cin.get();
        if (cin.eof())
        {
            return Token{quit};
        }
        else if (cin.fail())
        {
            return Token{quit};
        }
        else if (ch == '\n')
        {
            return Token{print};
        }
    }
    cin.putback(ch);
    cin >> ch;
    if (!cin)
    {
        exit(0);
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
    case '^':
    case ',':
    case '#':
    case '=':
        return Token{ch};
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
    {
        cin.putback(ch);  // Счёт числа с плавающей точкой
        double val;
        cin >> val;
        return Token{number, val};
    }

    default:
        if (isalpha(ch))  // Счет буквы из названия функции
        {
            string s;
            s += ch;  // Костыль
            while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_'))
            {
                s += ch;
            }
            if (ch == ctrlzchar)
            {
                exit(0);
            }
            cin.putback(ch);

            if (s == quitkey)
                return Token{quit};
            else if (s == sqrtkey)
                return Token{number, square_root()};
            else if (s == powkey)
                return Token{number, power()};
            else if (s == logkey)
                return Token{number, logarithm()};
            else if (s == sinkey)
                return Token{number, sine()};
            else if (s == coskey)
                return Token{number, cosine()};
            else if (s == constkey)
                return Token{constc};
            else if (s == helpkey || s == Helpkey)
                return Token{helpchar};
            return Token{name, s};
        }

        error("Bad token ");
    }
}

void Token_stream::ignore()  // скип до следующего \n
{
    if (full && buffer.kind == print)
    {
        cin.putback(buffer.kind);
        full = false;
        return;
    }

    full = false;

    while (cin)
    {
        char ch = cin.get();
        if (ch == print)
        {
            cin.putback(ch);
            return;
        }
    }
}

Token_stream ts;
