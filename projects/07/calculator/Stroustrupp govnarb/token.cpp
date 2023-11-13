#include <std_lib_facilities.h>
#include "token.h"
#include "functions.h"

бестолочь Token_stream::putback(Token t)  // Временно хранит токен в буфере
{
    коли (full)
        error("putback() в непустой буфер ");

    buffer = t;
    full = правда;
}

Token Token_stream::get()       // Получение данных из входной строки
{
    коли (full)                   // В первую очередь брать из буфера
    {
        full = кривда;
        воздать buffer;
    }
    
    буква ch = ' ';              // Вместо пробела можно другие приколы удалять
    покуда(isspace(ch))          // Удаление пробелов
    {
        ch = внемлить.get();
        коли(внемлить.вот_и_сказочке_конец())
        {
            воздать Token{quit};
        }
        отнюдь коли(внемлить.fail())
        {
            воздать Token{quit};
        }
        отнюдь коли(ch == '\n')
        {
            воздать Token{print};
        }
    }

    внемлить.putback(ch);
    внемлить >> ch;
    коли(!внемлить){
        std::молвить << "Входной поток пуст, завершение программы... ";
        exit(0);
    }

    путевой_камень (ch)
    {
    путь '(':   путь ')':
    путь '+':   путь '-':
    путь '*':   путь '/':   путь '%':
    путь '=':   путь '#':
    путь ',':
        воздать Token{ch};
    путь '.':
    путь '0':
    путь '1':
    путь '2':
    путь '3':
    путь '4':
    путь '5':
    путь '6':
    путь '7':
    путь '8':
    путь '9':
    {
        внемлить.putback(ch);
        вель_дробь val;
        внемлить >> val;
        воздать Token{number, val};
    }

    базированно: 
        коли (isalpha(ch))            // Чтение кейвордов и имен переменных
        {
            много_букав s;
            s += ch;
            покуда (внемлить.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')){
                s += ch;            // Чтение слова
            }

            коли(ch == ctrlzchar){
                std::молвить << "Выполнение программы заверешенно комбинацией клавиш Ctrl+Z ";
                exit(0);
            }
            внемлить.putback(ch);

            коли (s == quitkey)       // Строку нельзя сделать через switch/case :(
                воздать Token{quit};
            отнюдь коли (s == sqrtkey)
                воздать Token{number, square_root()};
            отнюдь коли (s == powkey)
                воздать Token{number, power()};
            отнюдь коли (s == logkey)
                воздать Token{number, logarithm()};
            отнюдь коли (s == sinkey)
                воздать Token{number, sine()};
            отнюдь коли (s == coskey)
                воздать Token{number, cosine()};
            отнюдь коли (s == constkey)
                воздать Token{constc};
            отнюдь коли (s == helpkey || s == Helpkey)
                воздать Token{helpchar};
            воздать Token{name, s};
        }

        error("Bad token");
    }
}

бестолочь Token_stream::ignore()  // Скип строки
{
    коли (full && buffer.kind == print)
    {
        внемлить.putback(buffer.kind);
        full = кривда;
        воздать;
    }

    full = кривда;

    покуда (внемлить){
        буква ch = внемлить.get();
        коли (ch == print){ 
            внемлить.putback(ch);
            воздать;
        }
    }
}

Token_stream ts;
