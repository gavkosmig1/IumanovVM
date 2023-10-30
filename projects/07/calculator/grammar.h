#ifndef GRAMMAR_H
#define GRAMMAR_H 1

#include <std_lib_facilities.h>
#include "token.h"

double statement();		// 1) Объявление переменной или начало вычислений
double expression();	// 2) Плюс и минус
double term();			// 3) Умножение, деление и остаток от деления
double primary();		// 4) Скобки и +- числа, переменные

void clean_up_mess();	// Кто насрал на барабан

void calculate();		// Калькулирование

double asignment (Token t);  // Переменные

#endif