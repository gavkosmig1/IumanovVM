# include "TokenStream.h"
inline void error(const std::string& input);

void calculate();
double expression(TokenStream& tokenStream);
double term(TokenStream& tokenStream);
double primary(TokenStream& tokenStream);
void keep_window_open(std::string& enterToClose);

int main()
{
    std::string enterToClose = "~~";
    try {
        calculate();
        keep_window_open(enterToClose);
        return 0; 
    }
    catch (std::exception& error) {
        std::cerr << error.what() << '\n';
        keep_window_open(enterToClose);
        return 1;
    }
    catch (...) {
        std::cerr << "Unknown exception!\n";
        keep_window_open(enterToClose);
        return 2;
    }
}

void calculate()
{
    const char quit = 'q';                                    // символ для токена выхода
    const char print = ';';                                  // символ для принт токена
    const std::string prompt = "> ";
    const std::string equals = "= ";                         // что выводится перед результатом
    TokenStream tokenStream;
    std::string enterToClose = "~~";                         // символы для закрытия окна
    while (std::cin)
        try
        {
            std::cout << prompt;
            Token token = tokenStream.getToken();

            if (token.kind == print)
                token = tokenStream.getToken();              // избавиться от точки с запятой

            if (token.kind == quit)
                break;

            tokenStream.setToken(token);
            std::cout << equals << expression(tokenStream) << '\n';
        }

        catch (std::exception& e)
        {
            std::cerr << e.what() << '\n';
            tokenStream.ignore(print);
        }
}

double expression(TokenStream& tokenStream)
{
    double result = term(tokenStream);                      // результат получает значение от term
    Token token = tokenStream.getToken();

    while (true)
    {
        if (token.kind == '+')
        {
            result += term(tokenStream);                    // подсчет следующего term и +
            token = tokenStream.getToken();
        }

        if (token.kind == '-')
        {
            result -= term(tokenStream);                    // подсчет следующего term и -
            token = tokenStream.getToken();
        }

        if (token.kind != '+' && token.kind != '-')
        {
            tokenStream.setToken(token);                    // иначе возвращаем в поток
            return result;
        }
    }
}

double term(TokenStream& tokenStream)
{
    double result = primary(tokenStream);                   // результат получает значение от primary
    Token token = tokenStream.getToken();

    while (true)
    {
        if (token.kind == '*')
        {
            result *= primary(tokenStream);                 // подсчет следующего primary и *
            token = tokenStream.getToken();
        }

        else if (token.kind == '/')
        {
            double divisor = primary(tokenStream);          // делитель получает значение от primary
            if (divisor == 0) error("divide by zero");
            result /= divisor;                             // и деление
            token = tokenStream.getToken();
        }

        else if (token.kind == '%')
        {
            int numer = result;                            // превращаем исходник в int
            int denom = primary(tokenStream);              // получаем int делитель
            if (denom == 0) error("%: divide by zero");
            result = numer % denom;                        // и остаток от деления
            token = tokenStream.getToken();
        }

        else
        {
            tokenStream.setToken(token);                  // иначе возвращаем в поток
            return result;
        }
    }
}

double primary(TokenStream& tokenStream)
{
    const char number = '8';                              // символ типа данных для чисел

    Token token = tokenStream.getToken();

    if (token.kind == '-') return -primary(tokenStream);

    else if (token.kind == '+') return primary(tokenStream);

    else if (token.kind == number) return token.value;    // возвращаем значение числа

    else if (token.kind == '(')
    {
        double result = expression(tokenStream);          // подсчет всего, что внутри скобок идет в result
        token = tokenStream.getToken();
        if (token.kind != ')') error("')' expected");
        return result;
    }

    else
        error("primary expected");
}

inline void error(const std::string& input)
{
    throw std::runtime_error(input);
}

inline void keep_window_open(std::string& enterToClose)
{
    std::string input= "input";
    std::cout << "Enter" << enterToClose <<"to close the window\n";
    while (std::getline(std::cin, input))
        if (input == enterToClose) break;                 // пока не введем символ выхода из окна, держим открытым
}
