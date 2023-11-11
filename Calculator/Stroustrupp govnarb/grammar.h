#ifndef GRAMMAR_H
#define GRAMMAR_H 1

#include <std_lib_facilities.h>
#include "token.h"

double statement();		// 1) ���������� ���������� ��� ������ ����������
double expression();	// 2) ���� � �����
double term();			// 3) ���������, ������� � ������� �� �������
double primary();		// 4) ������ � +- �����, ����������

void clean_up_mess();	// ��� ������ �� �������

void calculate();		// ���������������

double asignment (Token t);  // ����������

#endif