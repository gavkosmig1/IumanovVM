# pragma once
# include "Token.h"
# include <iostream>
# include <string>
# include <stdexcept>

class TokenStream
{
    public:
        TokenStream();
        void setToken(Token token);
        Token getToken();
        void ignore(char ch);
        void putback (Token t);

    protected:
    private:
        bool full {false};
        Token buffer;
};
