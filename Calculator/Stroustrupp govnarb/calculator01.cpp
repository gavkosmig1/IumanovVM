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

    try
    {
        calculate();
        keep_window_open(enterToClose);
        return 0;
    }

    catch (std::exception& error)
    {
        std::cerr << error.what() << '\n';
        keep_window_open(enterToClose);
        return 1;
    }

    catch (...)
    {
        std::cerr << "Unknown exception!\n";
        keep_window_open(enterToClose);
        return 2;
    }
}

void calculate()
{
    const char quit = 'q';       // t.kind==quit means that t is a quit Token
    const char print = ';';      // t.kind==print means that t is a print Token
    const std::string prompt = "> ";
    const std::string equals = "= ";  // used to indicate that what follows is an evaluation
    TokenStream tokenStream;
    std::string enterToClose = "~~";

    while (std::cin)
        try
        {
            std::cout << prompt;
            Token token = tokenStream.getToken();

            if (token.kind == print)
                token = tokenStream.getToken();   // eat ';'

            if (token.kind == quit)
                break;

            tokenStream.setToken(token);      // reset token into tokenStream
            std::cout << equals << expression(tokenStream) << '\n';
        }

        catch (std::exception& e)
        {
            std::cerr << e.what() << '\n';                      // write error message
            tokenStream.ignore(print);
        }
}

double expression(TokenStream& tokenStream)
{
    double result = term(tokenStream);       // set result to value of term
    Token token = tokenStream.getToken();  // get next token from tokenStream

    while (true)
    {
        if (token.kind == '+')
        {
            result += term(tokenStream);      // evaluate term and add to result
            token = tokenStream.getToken(); // get next token from tokenStream
        }

        if (token.kind == '-')
        {
            result -= term(tokenStream);      // evaluate term and subtract from result
            token = tokenStream.getToken(); // get next token from tokenStream
        }

        if (token.kind != '+' && token.kind != '-')
        {
            tokenStream.setToken(token);    // reset token into token stream
            return result;                    // return result
        }
    }
}

double term(TokenStream& tokenStream)
{
    double result = primary(tokenStream);   // set result to value of primary
    Token token = tokenStream.getToken(); // get next token from tokenStream

    while (true)
    {
        if (token.kind == '*')
        {
            result *= primary(tokenStream);   // evaluate primary and multiply with result
            token = tokenStream.getToken(); // get next token from tokenStream
        }

        else if (token.kind == '/')
        {
            double divisor = primary(tokenStream);     // set divisor to value of primary
            if (divisor == 0) error("divide by zero"); // check for error
            result /= divisor;                           // divide result by divisor
            token = tokenStream.getToken();      // get next token from tokenStream
        }

        else if (token.kind == '%') // modulo will only work on ints for this implementation
        {
            int numer = result; // cast result to int
            int denom = primary(tokenStream); // cast denom to int
            if (denom == 0) error("%: divide by zero"); // error check
            result = numer % denom; // get result
            token = tokenStream.getToken();      // get next token from tokenStream
        }

        else
        {
            tokenStream.setToken(token);   // put token back into the Token stream
            return result;                 // return result
        }
    }
}

double primary(TokenStream& tokenStream)
{
    const char number = '8';

    Token token = tokenStream.getToken();

    if (token.kind == '-') return -primary(tokenStream);

    else if (token.kind == '+') return primary(tokenStream);

    else if (token.kind == number) return token.value; // return the number’s value

    else if (token.kind == '(') // handle ‘(‘ expression ‘)’
    {
        double result = expression(tokenStream);      // set result to value of expression
        token = tokenStream.getToken();               // get next token from tokenStream
        if (token.kind != ')') error("')' expected"); // check for error
        return result;                                // return divisor
    }

    else // check for error
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
    while (std::getline(std::cin, input))         // keep reading until we find a ~
        if (input == enterToClose) break;
}

/*
          The grammar for input is:

          Statement:
                    Expression
                    Print
                    Quit
          Print:
                    ;

          Quit:
                    q

          Expression:
                    Term
                    Expression + Term
                    Expression – Term
          Term:
                    Primary
                    Term * Primary
                    Term / Primary
                    Term % Primary
          Primary:
                    Number
                    ( Expression )
                    – Primary
                    + Primary
          Number:
                    floating-point-literal

*/
