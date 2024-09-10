#ifndef Calculate_h
#define Calculate_h

#include "std_lib_facilities.h"

#include "Token_stream.h"
#include "Variables.h"

void print_help ();

double primary ();

double term ();

double expression ();

double declaration ();

double statement ();

void clean_up_mess ();

void calculator_start (Variables var_table, Token_stream ts, bool no_promt);

#endif
