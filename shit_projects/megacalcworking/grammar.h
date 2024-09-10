#ifndef GRAMMAR_H
#define GRAMMAR_H 1

#include "std_lib_facilities.h"
#include "token.h"

double statement ();  // Разделение входа на работу с переменными и числами

double expression ();  // Сложение и вычитание
double term ();        // Умножение, деление и остаток от деления
double powterm ();     // Степени
double primary ();     // +- числа и скобки

void clean_up_mess ();  // не принимает ничего, пока не придет \n

void calculate ();  // калькулирует

double asignment (Token t);  // Изменяет значение переменной

#endif