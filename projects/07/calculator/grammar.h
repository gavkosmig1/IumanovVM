#ifndef GRAMMAR_H
#define GRAMMAR_H 1

#include <std_lib_facilities.h>
#include "token.h"

double statement();		// 1) Разделение входа на объявление переменных, констант и вычисления
double expression();	// 2) Плюс, минус
double term();			// 3) Умножение, деление и остаток от деления
double primary();		// 4) Скобки, +- числа, переменные

void clean_up_mess();	// Скип строки

void calculate();		// Калькулирование

double asignment (Token t);  // Изменение значения существующей переменной

#endif