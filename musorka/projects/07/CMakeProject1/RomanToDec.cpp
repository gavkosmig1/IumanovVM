#include "std_lib_facilities.h"
#include <algorithm>
#include <iostream>
#include <vector>

vector<string> suite ()
{
    const static string roman[][10U] = {{"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"},
                                        {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"},
                                        {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"},
                                        {"", "M", "MM", "MMM"}};
    vector<string> box;
    for (auto i = 0U; i < 3999U; ++i)
    {
        string str;
        if (i / 1000)
            str += roman[3][i / 1000 % 10];
        if (i / 100)
            str += roman[2][i / 100 % 10];
        if (i / 10)
            str += roman[1][i / 10 % 10];
        if (i)
            str += roman[0][i % 10];
        box.push_back(str);
    }
    return box;
}

unsigned arabic (string roman)
{
    const static vector<string> box = suite();
    transform(roman.begin(), roman.end(), roman.begin(), ::toupper);
    auto pos = find(box.begin(), box.end(), roman);
    if (pos == box.end())
        return 0;
    return pos - box.begin();
}