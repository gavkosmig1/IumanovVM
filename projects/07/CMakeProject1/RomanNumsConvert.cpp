#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <map>

using namespace std;


void ThrowEmptyStringError()
{
    throw string("Rome value is empty string.");
}

void ThrowBadFormatError(const string& val)
{
    throw "The \"" + val + "\" has incorrect rome number format.";
}

void ThrowOutOfRangeOrBadFormatError(const string& val)
{
    throw "The \"" + val + "\" is greater than 3999 or has incorrect rome number format.";
}

void ThrowBadConversionError(const string& romeVal, const unsigned correctVal, unsigned conversionResult)
{
    ostringstream oss;
    oss << "The \"" + romeVal + " == " << correctVal << "\" is converted to " << conversionResult << ".";
    throw string(oss.str());
}


const unsigned BAD_VALUE = (unsigned)-1;
typedef pair<string, unsigned> RomeDecPair;
typedef map<string, unsigned> Table;
Table g_table;

void InitTables()
{
    g_table["I"] = 1;
    g_table["II"] = 2;
    g_table["III"] = 3;
    g_table["IV"] = 4;
    g_table["V"] = 5;
    g_table["VI"] = 6;
    g_table["VII"] = 7;
    g_table["VIII"] = 8;
    g_table["IX"] = 9;
    g_table["X"] = 10;
    g_table["XX"] = 20;
    g_table["XXX"] = 30;
    g_table["XL"] = 40;
    g_table["L"] = 50;
    g_table["XC"] = 90;
    g_table["C"] = 100;
    g_table["CC"] = 200;
    g_table["CCC"] = 300;
    g_table["CD"] = 400;
    g_table["D"] = 500;
    g_table["CM"] = 900;
    g_table["M"] = 1000;
    g_table["MM"] = 2000;
    g_table["MMM"] = 3000;
}

bool StartsWith(const string& romeVal, const string& pattern)
{
    if (romeVal.length() >= pattern.length())
        return romeVal.substr(0, pattern.length()) == pattern;
    return false;
}

string GetFirstRomeValue(const string& romeVal)
{
    unsigned maxDecVal = 0;
    const string* result = 0;
    for (Table::const_iterator it = g_table.begin(), end = g_table.end(); it != end; ++it)
    {
        const string& currentRomeVal = it->first;
        const unsigned currentDecVal = it->second;
        if (StartsWith(romeVal, currentRomeVal) && currentDecVal > maxDecVal)
        {
            if (currentRomeVal.length() == 1)
            {
                if (StartsWith(romeVal, string(4, currentRomeVal[0])))
                    ThrowBadFormatError(romeVal);
            }

            result = &currentRomeVal;
            maxDecVal = currentDecVal;
        }
    }

    if (result == 0)
        ThrowBadFormatError(romeVal);

    return *result;
}

unsigned RomeToDec(const string& romeVal)
{
    if (romeVal.empty())
        ThrowEmptyStringError();

    string str = romeVal;
    unsigned result = 0;
    unsigned prevDecVal = 0;
    while (!str.empty())
    {
        const string tmpRomeVal = GetFirstRomeValue(str);
        const unsigned tmpDecVal = g_table[tmpRomeVal];

        if (prevDecVal != 0 && prevDecVal <= tmpDecVal)
            ThrowBadFormatError(romeVal);

        prevDecVal = tmpDecVal;
        result += tmpDecVal;

        if (result >= 4000)
            ThrowOutOfRangeOrBadFormatError(romeVal);

        str = str.substr(tmpRomeVal.length());
    }
    return result;
}


void CheckConversion(const RomeDecPair& test)
{
    try
    {
        const unsigned result = RomeToDec(test.first);
        if (result == test.second)
        {
            cout << test.first << " == " << test.second << endl;
        }
        else
        {
            ThrowBadConversionError(test.first, test.second, result);
        }
    }
    catch (const string& errDescr)
    {
        cout << (test.first.empty() ? "#empty#" : test.first.c_str()) << ": failed : " << errDescr << endl;
    }
}