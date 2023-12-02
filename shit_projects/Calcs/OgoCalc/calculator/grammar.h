#ifndef GRAMMAR_H
#define GRAMMAR_H 1

#include <std_lib_facilities.h>
#include "token.h"

double statement(); //0'th level of grammar (divides either into regular grammar path or variable grammar path)

//GRAMMAR

double expression(); //1'st level
double term();       //2'nd level
double powterm();    //3'rd level
double factterm();   //4'th level
double primary();    //5'th level

//END OF GRAMMAR

void clean_up_mess();           //ignores everything until ('\n')

void calculate();               //performs calculation cycle

double asignment (Token t);     //redefines a variable

#endif