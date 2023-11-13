#include "token.h"
#include "functions.h"
#include <std_lib_facilities.h>

void Token_stream::putback(Token t)  // Временно хранит токен в буфере
{
    if (full)
        error("putback() в непустой буфер ");

    buffer = t;
    full = true;
}

Token Token_stream::get()  // Получение данных из входной строки
{
    if (full)  // В первую очередь брать из буфера
    {
        full = false;
        return buffer;
    }

    char ch = ' ';       // Вместо пробела можно другие приколы удалять
    while (isspace(ch))  // Удаление пробелов
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
        std::cout << "Входной поток пуст, завершение программы... ";
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
    case '=':
    case '#':
    case ',':
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
        cin.putback(ch);
        double val;
        cin >> val;
        return Token{number, val};
    }

    default:
        if (isalpha(ch))  // Чтение кейвордов и имен переменных
        {
            string s;
            s += ch;
            while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_'))
            {
                s += ch;  // Чтение слова
            }

            if (ch == ctrlzchar)
            {
                std::cout << "Выполнение программы заверешенно комбинацией клавиш Ctrl+Z ";
                exit(0);
            }
            cin.putback(ch);

            if (s == quitkey)  // Строку нельзя сделать через switch/case :(
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

        error("Bad token");
    }
}

void Token_stream::ignore()  // Скип строки
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
