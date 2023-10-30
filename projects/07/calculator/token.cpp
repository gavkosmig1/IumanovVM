#include <std_lib_facilities.h>
#include "token.h"
#include "functions.h"

void Token_stream::putback(Token t)  // ���������� ������ � �����
{
    if (full)
        error("putback() into a full buffer ");

    buffer = t;
    full = true;
}

Token Token_stream::get()  // ������ ������� � ������ �����
{
    if (full)  // ������ � ������
    {
        full = false;
        return buffer;
    }
    
    char ch = ' ';
    while(isspace(ch))  // ���� ��������
    {
        ch = cin.get();
        if(cin.eof())
        {
            return Token{quit};
        }
        else if(cin.fail())
        {
            return Token{quit};
        }
        else if(ch == '\n')
        {
            return Token{print};
        }
    }

    cin.putback(ch);
    cin >> ch;
    if(!cin){
        std::cout << "������ � ������������� �������� ";
        exit(0);
    }
    switch (ch)
    {
    case '(':   case ')':
    case '+':   case '-':
    case '*':   case '/':   case '%':
    case '=':   case '#':
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
        if (isalpha(ch)) //checks for key words
        {
            string s;
            s += ch; //if while doesn't activate
            while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')){
                s += ch;
            }
            if(ch == ctrlzchar){
                std::cout << "Goodbye :)";
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

        error("Bad token");
    }
}

void Token_stream::ignore() //ignores everything until printkey appears ('\n')
{
    if (full && buffer.kind == print)
    {
        cin.putback(buffer.kind);
        full = false;
        return;
    }

    full = false;

    while (cin){
        char ch = cin.get();
        if (ch == print){ 
            cin.putback(ch);
            return;
        }
    }
}

Token_stream ts;
