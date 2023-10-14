#include "TokenStream.h"

TokenStream::TokenStream() {}  // а комментарии обязательно на одном уровне ставить?

void TokenStream::setToken(Token token)
{
    if (full)
        throw std::runtime_error("setToken() into a full buffer");
    buffer = token;            // копирует вхлд в буфер
    full = true;               // теперь в буфере полон
}

Token TokenStream::getToken()
{
    const char number = '8';   // хранящийся символ для числа
    const char quit = 'q';     // символ для выхода из проги
    const char print = ';';    // символ для вывода

    if (full)                  // если в буфере уже есть токен
    {
        full = false;          // буфер опустошается и выводится из функции
        return buffer;
    }

    char ch;
    std::cin >> ch;            // ввод символа

    switch (ch)                // анализируем состав входа
    {
    case print:
    case quit:
    case '(':
    case ')':
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case '^':                   // Степень
        return Token {ch};      // если символ, то возвращаем его же
    case 'k':
        return Token {number, 1000};
    case '.':
    case '0':    case '1':    case '2':    case '3':    case '4':
    case '5':    case '6':    case '7':    case '8':    case '9':
    {
        std::cin.putback(ch);   // а если число, возвращем его в поток входа
        double val;
        std::cin >> val;        // и считываем число полностью
        return Token {number, val};
    }

    default:
        throw std::runtime_error("Bad token");
    }
}

void TokenStream::ignore(char ch)
{
    if (full && ch == buffer.kind) {
        full = false;
        return;
    }                     // если че-то есть в буфере, он очищается
    full = false;
    char ch2 = 0;         // иначе ищем этот символ в потоке входа
    while (std::cin >> ch)
        if (ch2 == ch) return;
}
