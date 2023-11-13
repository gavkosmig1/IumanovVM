#include "TokenStream.h"

TokenStream::TokenStream() {} //ctor

void TokenStream::setToken(Token token)
{
    if (full)
        throw std::runtime_error("setToken() into a full buffer");
    buffer = token;             // copy token to buffer
    full = true;            // buffer is now full
}

Token TokenStream::getToken()
{
    const char number = '8'; // let ‘8’ represent “a number”
    const char quit = 'q';       // t.kind==quit means that t is a quit Token
    const char print = ';';      // t.kind==print means that t is a print Token

    if (full)               // do we already have a Token ready?
    {
        full = false;       // remove Token from buffer
        return buffer;
    }

    char ch;
    std::cin >> ch;         // skips whitespace (space, newline, tab, etc.)

    switch (ch)
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
        return Token {ch};  // let each character represent itself
    case '.':
    case '0':    case '1':    case '2':    case '3':    case '4':
    case '5':    case '6':    case '7':    case '8':    case '9':
    {
        std::cin.putback(ch);   // put digit back into the input stream
        double val;
        std::cin >> val;        // read a floating-point number
        return Token {number, val};
    }

    default:
        throw std::runtime_error("Bad token");
    }
}

void TokenStream::ignore(char ch)
{
          // first look in buffer:
          if (full && ch == buffer.kind) {
                    full = false;
                    return;
          }

          full = false;

          // now search input:
          char ch2 = 0;
          while (std::cin >> ch)
                    if (ch2 == ch) return;
}
