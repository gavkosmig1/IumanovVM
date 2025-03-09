#include "std_lib_facilities.h"
#include <cstdlib>
#include <iostream>
#include <locale>

using std::cin;
using std::cout;
using std::locale;

bool Is_roman_Num (string t)
{
    locale::global(locale(""));

    string r[13] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    size_t b, i;  // ������ �������� ������� � ������ � ������ ������� ������� ����� � ������� r

    for (b = 0, i = 0; b < t.length() && i < 13; ++i)
    {
        size_t rl = r[i].length();  // ���������� �������� � �������� �������
        if (t.substr(b, rl) == r[i])
        {
            if (rl == 1 && i != 0)
            {
                size_t count = 1;  // ���������� ��������
                while (++b < t.length() && t.substr(b, rl) == r[i])
                    ++count;  // ������� � ������� ������������� ����
                if (count > 3)
                {
                    --b;
                    break;
                }
            }
            else
                b += rl;
        }
    }

    if (b < t.length())
    {
        return false;
    }
    else
    {
        return true;
    }
}