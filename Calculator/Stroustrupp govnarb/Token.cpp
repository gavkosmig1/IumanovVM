#include "Token.h"

Token::Token() {} //ctor

Token::Token(char kind) : kind(kind), value (0) {} // ctor

Token::Token(char kind, double value) : kind(kind), value(value) {} //ctor
