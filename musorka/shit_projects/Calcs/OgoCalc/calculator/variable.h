#ifndef VARIABLE_H
#define VARIABLE_H 1

#include <std_lib_facilities.h>

struct Variable
{
    string name;
    double value;
    bool isconstant;

    Variable(string n, double v, bool isc) : name{n}, value{v}, isconstant{isc} {}
};

class Symbol_table //Class, that contains variables and constants
{
    public:
        vector<Variable> v;  // Vector of declared variables/constants

        Symbol_table(vector<Variable> v_t) : v{v_t} {}

        double get_value (const string& s);                             //Gets value from vector if name exists, 
                                                                        //throws error otherwise

        bool is_declared (const string& s);                             //Checks if name is declared

                                                                        //Sets value for name in vector if it is
        double set_value (const string& s, double d);                   //a variable, if it's a constant or name
                                                                        //doesn't exist, throws an error

                                                                        //Adds value into the vector of variables
        double define_name (const string& var, double val, bool icg);   //Throws an error if the variable was
                                                                        //Already declared
};

void replacement(string var, double val);

double declaration (bool is_const);

extern vector<Variable> var_table;
extern Symbol_table symbol_table;

#endif