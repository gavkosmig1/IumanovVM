#include "std_lib_facilities.h"
#include <iostream>

string func (int num, string, string, string);

string DecToRoman (int arabien_num)
{
    if (1 > arabien_num || arabien_num > 4000)
        error("Roman numbers can be in diapazon 1 - 4000");
    string rome_num;

    rome_num += func(arabien_num / 1000, "", "", "M");
    arabien_num %= 1000;
    rome_num += func(arabien_num / 100, "M", "D", "C");
    arabien_num %= 100;
    rome_num += func(arabien_num / 10, "C", "L", "X");
    arabien_num %= 10;
    rome_num += func(arabien_num, "X", "V", "I");
    return rome_num;
}

string func (int num, string hi, string re, string lo)
{
    switch (num)
    {
    case 9:
        return (lo + hi).c_str();
    case 8:
        return (re + lo + lo + lo).c_str();
    case 7:
        return (re + lo + lo).c_str();
    case 6:
        return (re + lo).c_str();
    case 5:
        return (re).c_str();
    case 4:
        return (lo + re).c_str();
    case 3:
        return (lo + lo + lo).c_str();
    case 2:
        return (lo + lo).c_str();
    case 1:
        return (lo).c_str();
    case 0:
        return "";
    }
}