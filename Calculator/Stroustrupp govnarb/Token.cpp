#include "Token.h"

Token::Token() {} // Пустой токен

Token::Token(char kind) : kind(kind), value (0) {} // Токен символа (со значением 0)

Token::Token(char kind, double value) : kind(kind), value(value) {} // полноценный токен