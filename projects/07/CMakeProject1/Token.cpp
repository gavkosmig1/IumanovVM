#include "std_lib_facilities.h"

#include "Token.h"

Token::Token(char ch) : kind{ch}, value{0} {}

Token::Token(char ch, string nam) : kind{ch}, value{0}, name{nam} {}

Token::Token(char ch, double val) : kind{ch}, value{val} {};