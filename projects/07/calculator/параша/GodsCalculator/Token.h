# pragma once

class Token
{
    public:
        char kind;
        double value;
        Token();
        Token(char kind);
        Token(char kind, double value);
};
